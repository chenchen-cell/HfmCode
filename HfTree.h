//程序名：HfTree.h
//程序功能：定义霍夫曼树类，进行文本压缩
//作者：陈宇权
//日期：2021.12.3
//版本：1.0
//修改内容：无
//修改日期：无
//修改作者：无
//
//

#pragma once
#include"MinHeap.h"
#include"myStack.h"
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class HfTree {	//定义霍夫曼类
public:
	//构造函数
	HfTree(CntNode array[], int sz);
	HfTree();
	//析构函数
	~HfTree() {
		delete[] arr;
		delete[] table;
		if (root) {
			destory(root);
		}
	}
	void printTable();	//打印每个字符对应的编码表
	void save();		//保存霍夫曼树
	string toCode(char c);	//把字符变成对应字符串
	void impress(string s);		//压缩
	void decode(string codeFile, string TextFile);	//解码
	void display();	//打印霍夫曼树
private:
	CntNode* arr;	//arr数组保存每个字符以及对应权值
	int size;		//size为进行编码的字符数量
	HfNode* root;	//霍夫曼数根节点
	string table[128];	//table为128个字符对应的字符编码数组

	HfNode* merge(HfNode* l, HfNode* r);		//合并两棵树
	string encodeNode(HfNode* node);		//编码一个结点的字符
	void encode(HfNode* p);		//对一棵树的叶子进行编码
	unsigned char exchChar(char arr[8]);		//将字符串转换为unsigned char
	string charToStr(unsigned char num);		//把unsigned char 转换为string
	void display(HfNode* node, int cnt, int vec_left[], string &s);	//打印霍夫曼树
	void destory(HfNode* node);	//销毁函数
};

//////////////////////////////////////////////////////////////////////////////
// 构造函数
// 函数功能：根据字符以及出现频数初始化霍夫曼树
//函数参数：array为保存字符及出现频数的数组，sz为出现的字符数量
//参数返回值：无
HfTree::HfTree(CntNode array[], int sz) {

	arr = array;		//初始化arr
	size = sz;		//初始化sz

	//用最小堆进行霍夫曼树
	MinHeap* mh = new MinHeap(array, sz);

	HfNode* first;	
	HfNode* second;		
	HfNode* parent;
	while (mh->getLast()) {		//循环条件为堆中元素个数大于1
		mh->remove(first);	//第一次取最小
		mh->remove(second);	//第二次取最小
		parent = merge(first, second);	//两个结点进行合并
		mh->insert(parent);		//将双亲结点进行插入
	}
	mh->remove(parent);		//取堆中最后一个元素作为霍夫曼树的根节点
	root = parent;
	root->parent = 0;

	encode(root);	//初始化table数组
}

//////////////////////////////////////////////////////////////////////////////
// 构造函数
// 函数功能：根据hfmTree.dat文件初始化霍夫曼树
//函数参数：无
//参数返回值：无
HfTree::HfTree() {
	//读取文件数据
	ifstream is;
	int sz = 0;		//sz为CntNode数组大小
	is.open("hfmTree.dat", ios::binary | ios::in);
	is.read((char*)&(sz), sizeof(int));
	CntNode* array = new CntNode[sz];	//申请内存空间
	for (int i = 0; i < sz; i++) {
		is.read((char*)&(array[i].letter), sizeof(char));
		is.read((char*)&(array[i].cont), sizeof(int));
	}
	is.close();
	//初始化size和arr
	size = sz;
	arr = array;
	//利用最小堆构造霍夫曼树
	MinHeap* mh = new MinHeap(array, sz);

	HfNode* first;
	HfNode* second;
	HfNode* parent;
	while (mh->getLast()) {
		mh->remove(first);
		mh->remove(second);
		parent = merge(first, second);
		mh->insert(parent);
	}
	mh->remove(parent);
	root = parent;
	root->parent = 0;
	encode(root);	//初始化table数组
}

//////////////////////////////////////////////////////////////////////////////
// 合并函数
// 函数功能：将两个结点合并为一棵树，返回双亲结点
//函数参数：l为左节点，r为右节点
//参数返回值：parent为双亲结点
HfNode* HfTree::merge(HfNode* l, HfNode* r) {

	HfNode* parent = new HfNode;
	//对双亲结点以及孩子结点进行赋值
	parent->left = l;
	parent->right = r;
	parent->cont = l->cont + r->cont;	//parent的权值为孩子权值相加
	parent->parent = 0;
	l->parent = r->parent = parent;

	return parent;
}

//////////////////////////////////////////////////////////////////////////////
// 叶子结点编码函数
// 函数功能：对叶子结点的字符进行编码
//函数参数：node为要进行编码的叶子结点
//参数返回值：s为该字符对应编码的字符串
string HfTree::encodeNode(HfNode* node) {

	myStack<HfNode*> ms;		//声明一个栈
	HfNode* p = node;
	while (p) {		//将该结点的祖先从下往上依次压栈
		ms.push(p);
		p = p->parent;
	}

	string s = "";		//s为对应编码的字符串
	ms.pop(p);
	HfNode* follow;
	while (!ms.isEmpty()) {
		ms.pop(follow);
		//依次弹栈，若为左孩子编码为0
		if (follow == p->left) {
			s = s + '0';
		}
		//若为右孩子编码为1
		else if(follow==p->right){
			s = s + '1';
		}
		p = follow;
	}
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// 编码函数
// 函数功能：对一棵树的叶子结点进行编码
//函数参数：p为根节点
//参数返回值：无
void HfTree::encode(HfNode* p) {
	if (p->left) {		//循环遍历整棵树
		encode(p->left);
	}
	if (p->right) {
		encode(p->right);
	}
	//如果是叶子结点，则进行编码
	if (p->left == 0 && p->right == 0) {
		int index = p->letter;
		table[index] = encodeNode(p);	//将叶子结点编码的结构存入table数组
	}
}

//////////////////////////////////////////////////////////////////////////////
// 保存函数
// 函数功能：将霍夫曼树存入文件hfmTree.dat
//函数参数：无
//参数返回值：无
void HfTree::save() {
	ofstream os;
	os.open("hfmTree.dat", ios::binary);
	os.write((char*)&size, sizeof(int));		//存入字符的多少
	for (int i = 0; i < size; i++) {
		os.write((char*)&(arr[i].letter), sizeof(char));		//存入字符
		os.write((char*)&(arr[i].cont), sizeof(int));		//存入出现频数
	}
	os.close();
}

//////////////////////////////////////////////////////////////////////////////
// 转换函数
// 函数功能：根据字符得到对应编码
//函数参数：c为要转换的字符
//参数返回值：table[c]为对应的编码
string HfTree::toCode(char c) {		
	return table[c];
}

//////////////////////////////////////////////////////////////////////////////
// 压缩函数
// 函数功能：将整个字符集编码后存入文件
//函数参数：s为字符集
//参数返回值：无
void HfTree::impress(string s) {
	
	string str = "";
	for (int i = 0; i < s.length(); i++) {	//把s变成全是0/1的字符串，存入str
		str = str + table[s[i]];
	}
	//计算str/8与str%8，得到要将str转成多少个字符（length+1），需要补多少个'0'（rest）
	int length = str.length() / 8;
	int rest = str.length() % 8;
	for (int i = 0; i < 8 - rest; i++) {		//补'0',将字符串长度凑成8的倍数
		str = str + '0';
	}
	length++;

	ofstream os;
	os.open("codeFile.dat", ios::binary);
	//存入length以及rest
	os.write((char*)&(length), sizeof(int));
	os.write((char*)&(rest), sizeof(int));

	//把字符串存入unsigned char数组
	for (int i = 0; i < length; i++) {

		string temp = str.substr(i * 8, 8);	//str中每8位进行一次截取，转换为对应的字符
		char s[8];
		for (int k = 0; k < 8; k++) {
			s[k] = temp[k];
		}

		unsigned char num = exchChar(s);		//将字符串转换为要存入文件的unsigned char
		os.write((char*)&(num), sizeof(unsigned char));
	}
	os.close();
}

//////////////////////////////////////////////////////////////////////////////
// 转换函数
// 函数功能：将字符串转化为CntNode数组用于霍夫曼树的初始化
//函数参数：str为要编码的字符串，cont记录出现了多少种字符
//参数返回值：arr为返回的数组
CntNode* strToCnt(string str, int& cont) {
	CntNode** letterArray = new CntNode * [128];
	for (int i = 0; i < 128; i++) {
		letterArray[i] = 0;
	}
	//统计文章中字符数
	for (int i = 0; str[i] != '\0'; i++) {
		char c = str[i];
		if (letterArray[c] == 0) {
			letterArray[c] = new CntNode;
			letterArray[c]->cont = 1;
			letterArray[c]->letter = c;
			cont++;
		}
		else {
			letterArray[c]->cont++;
		}
	}
	//生成CntNode数组
	CntNode* arr = new CntNode[cont];
	int index = 0;
	for (int i = 0; i < 128; i++) {
		if (letterArray[i]) {	//若对应位置不为空，则添加到数组上
			arr[index].cont = letterArray[i]->cont;
			arr[index].letter = letterArray[i]->letter;
			index++;
		}
	}
	return arr;
}

//////////////////////////////////////////////////////////////////////////////
// 译码函数
// 函数功能：将二进制文件译码，并把结构写入文件
//函数参数：codeFile为压缩文件，TextFile为将结果写入的文件
//参数返回值：无
void HfTree::decode(string codeFile, string TextFile) {
	ifstream is;
	int lenght = 0, rest = 0;
	//读出压缩文件信息
	is.open(codeFile, ios::binary | ios::in);
	is.read((char*)&(lenght), sizeof(int));
	is.read((char*)&(rest), sizeof(int));

	string str = "";
	//把信息生成字符串
	unsigned char num = 0;
	for (int i = 0; i < lenght; i++) {
		is.read((char*)&(num), sizeof(unsigned char));
		string temp = charToStr(num);	//把对应的unsigned char数据转换为字符串
		str = str + temp;	//进行字符串的拼接

	}
	str = str.substr(0, (lenght - 1) * 8 + rest);
	is.close();		//关闭流
	
	string text = "";	//存储译码结果的字符串
	HfNode* p = root;	//遍历霍夫曼树的指针
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '0') {		//0往左走
			p = p->left;
		}
		else {		//否则往右走
			p = p->right;
		}

		if (p->left == 0 && p->right == 0) {		//如果是叶子结点则进行译码
			text = text + (p->letter);
			p = root;
		}
	}
	ofstream os;
	os.open(TextFile);		//将解码结果写入文件
	os << text;
	os.close();
}
//////////////////////////////////////////////////////////////////////////////
// 转换函数
// 函数功能：将字符数组转换为unsigned char类型的数据用于存储
//函数参数：arr为要转换的字符数组
//参数返回值：num为要进行存储的unsigned char数据
unsigned char HfTree::exchChar(char arr[8]) {
	unsigned char num = 0;
	for (int i = 0; i < 8; i++) {
		unsigned char k = arr[7-i] - 48;
		num = 2 * num;
		num += k;
	}
	return num;
}
//////////////////////////////////////////////////////////////////////////////
// 转换函数
// 函数功能：将unsigned char数据转换为对应的字符串
//函数参数：num为要进行转换的数据
//参数返回值：s为num对应的字符串
string HfTree::charToStr(unsigned char num) {
	char str[9];
	for (int i = 0; i < 8; i++) {
		int temp = num % 2 + 48;		//对2取余+48，得到对应字符的ascll码
		num = num / 2;	
		str[i] = temp;
		if (num == 0) {
			str[i + 1] = '\0';
		}
	}
	string s = str;
	return s;
}
//////////////////////////////////////////////////////////////////////////////
// 打印函数
// 函数功能：直观打印霍夫曼树
//函数参数：无
//参数返回值：无
void HfTree::display() {

	int cnt = 0;
	int vec_left[130];		//定义vec_left数组，用于记录每一行需要打印的" "数量
	HfNode* p = root;
	string s = "";

	for (int i = 0; i < 130; i++) {		//做初始化
		vec_left[i] = 1;
	}

	display(p, cnt, vec_left, s);	//调用结点打印函数

	ofstream os;		//把树的字符形式写入文件
	os.open("treePrin.txt");
	os << s;
	os.close();
}
//////////////////////////////////////////////////////////////////////////////
// 结点打印函数
// 函数功能：打印霍夫曼树的结点
//函数参数：node为要打印的结点，cnt与vec_left记录每行打印" "的数量，s为记录打印结果的字符串
//参数返回值：无
void HfTree::display(HfNode* node, int cnt, int vec_left[], string& s) {

	if (node != root) {		//如果不是根结点，打印" "
		cout << " ";
		s = s + " ";
	}

	if (cnt > 0) {		//打印该行对应的" "、"| "、"|--"
		for (int i = 0; i < cnt - 1; i++) {

			if (vec_left[i]) {
				cout << "| ";
				s = s + "| ";
			}
			else {
				cout << "  ";
				s = s + "  ";
			}

		}
		if (vec_left[cnt - 1]) {
			s = s + "|--";
			cout << "|--";
		}
		else {
			s = s + "\--";
			cout << "\--";
		}
	}

	//若为叶子结点，打印字符和对应的编码
	if (!node->left && !node->right) {
		cout<< node->letter << "-->" << table[node->letter] << endl;
		s = s + node->letter + "-->" + table[node->letter] + "\n";
		return;
	}
	else {		//若不是叶子结点，打印一个方块
		cout << "■\n";
		s = s + "■\n";
	}

	if (node->left) {
		vec_left[cnt] = 1;
		display(node->left, cnt + 1, vec_left, s);	//打印左子树
	}
	if (node->right) {
		vec_left[cnt] = 0;
		display(node->right, cnt + 1, vec_left, s);	//打印右子树
	}
}

void HfTree::destory(HfNode* node) {
	if (node->left) {
		destory(node->left);
	}
	if (node->right) {
		destory(node->right);
	}
	delete node;
}

void HfTree::printTable() {
	for (int i = 0; i < 128; i++) {
		char c = i;
		cout << c << " -----> " << table[i] << endl;
	}
}