//程序名：main.cpp
//程序功能：利用霍夫曼树进行文本压缩
//作者：陈宇权
//日期：2021.12.23
// 版本：1.0
// 修改内容：无
// 修改日期：
// 修改作者：
//

#include"HfTree.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
void menu() {	//菜单，显示相应的功能
	cout << "----选择数字进行相应的操作----" << endl;
	cout << "\t1----------初始化" << endl;
	cout << "\t2----------编码" << endl;
	cout << "\t3----------译码" << endl;
	cout << "\t4----------打印代码文件" << endl;
	cout << "\t5----------打印霍夫曼树" << endl;
	cout << "\t6----------退出系统" << endl;
}

void initialize();		//初始化霍夫曼树
void encode();			//进行编码
void decode();			//进行译码
void print();			//以二进制形式打印代码文件
void treePrint();		//打印霍夫曼树

void(*Function[5])(void) = { initialize, encode, decode, print, treePrint };


string getStr();		//获取文件对应的字符串
string getStr(string text);		//获取文件text对应的字符串
HfTree* myTree = 0;		//定义霍夫曼树对象的指针

//////////////////////////////////////////////////////////////////////////////
//  主函数
//  返回值：0
int main() {
	int choose = 0;		//根据choose的值选择相应的功能
	while (true) {
		menu();
		cin >> choose;
		if (choose == 6)break;	//结束循环，退出系统
		if (choose >= 1 && choose <= 5) {	//执行相应的功能
			Function[choose - 1]();
		}
		else {
			cout << "输入不合法！！！请重新输入\n";
		}
	}
	return 0;
}

void initialize() {		//初始化函数
	cout << "请输入要编码的文章文件名\t";
	string text;
	cin >> text;
	//读取文章转换为字符串
	string str = getStr(text);
	
	int cont = 0;	//记录出现了多少字符
	CntNode* arr = strToCnt(str, cont);		//声明数组用于统计文章字符的频数
	
	myTree = new HfTree(arr, cont);	//生成并初始化霍夫曼树

	myTree->save();	//保存
	cout << "霍夫曼树初始化成功" << endl;
}

void encode() {		//编码函数
	if (myTree == 0) {	//若霍夫曼树不存在，则从文件中读入进行初始化
		myTree = new HfTree;
	}
	string s;
	cout << "请输入要编码的文章的名字\t";
	cin >> s;
	string str = getStr(s);	//获取文章内容，存入字符串str

	myTree->impress(str);	//进行压缩
	cout << "文件编码成功" << endl;
}

void decode() {		
	if (myTree == 0) {	//若霍夫曼树不存在，则从文件中读入
		myTree = new HfTree;
	}
	myTree->decode("codeFile.dat", "TextFile.txt");		//将编码的结果进行译码，结果存入TextFile.txt
	cout << "文件译码成功" << endl;
}

void print() {
	if (myTree == 0) {	//若霍夫曼树不存在，则从文件中读入
		myTree = new HfTree;
	}
	cout << "请输入要编码的文章文件名\t";
	string text;
	cin >> text;

	string str = getStr(text);	//读取文章转换为字符串

	string code = "";	//code为编码的字符串
	for (int i = 0; str[i] != '\0'; i++) {		//对每一个字符进行编码
		code = code + myTree->toCode(str[i]);
	}
	//以字符形式将编码写入文件
	ofstream os;
	os.open("CodePrin.txt");
	os << code;
	os.close();
	//打印到控制端
	for (int i = 0; code[i] != '\0'; i++) {
		if (i % 50 == 0) {
			cout << endl;
		}
		cout << code[i];
	}
	cout << endl;
}

void treePrint() {
	if (!myTree) {	//若霍夫曼树不存在，则从文件中读入
		myTree = new HfTree;
	}
	myTree->display();	//打印霍夫曼树
	cout << endl;
}

string getStr() {	//从文件读入内容并返回字符串
	fstream fs("text.txt");
	stringstream ss;
	ss << fs.rdbuf();
	string str = ss.str();
	fs.close();
	return str;
}

string getStr(string text) {		//从文件text读入内容并返回字符串	
	fstream fs(text);
	stringstream ss;
	ss << fs.rdbuf();
	string str = ss.str();
	fs.close();
	return str;
}

