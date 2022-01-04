//��������HfTree.h
//�����ܣ�������������࣬�����ı�ѹ��
//���ߣ�����Ȩ
//���ڣ�2021.12.3
//�汾��1.0
//�޸����ݣ���
//�޸����ڣ���
//�޸����ߣ���
//
//

#pragma once
#include"MinHeap.h"
#include"myStack.h"
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class HfTree {	//�����������
public:
	//���캯��
	HfTree(CntNode array[], int sz);
	HfTree();
	//��������
	~HfTree() {
		delete[] arr;
		delete[] table;
		if (root) {
			destory(root);
		}
	}
	void printTable();	//��ӡÿ���ַ���Ӧ�ı����
	void save();		//�����������
	string toCode(char c);	//���ַ���ɶ�Ӧ�ַ���
	void impress(string s);		//ѹ��
	void decode(string codeFile, string TextFile);	//����
	void display();	//��ӡ��������
private:
	CntNode* arr;	//arr���鱣��ÿ���ַ��Լ���ӦȨֵ
	int size;		//sizeΪ���б�����ַ�����
	HfNode* root;	//�����������ڵ�
	string table[128];	//tableΪ128���ַ���Ӧ���ַ���������

	HfNode* merge(HfNode* l, HfNode* r);		//�ϲ�������
	string encodeNode(HfNode* node);		//����һ�������ַ�
	void encode(HfNode* p);		//��һ������Ҷ�ӽ��б���
	unsigned char exchChar(char arr[8]);		//���ַ���ת��Ϊunsigned char
	string charToStr(unsigned char num);		//��unsigned char ת��Ϊstring
	void display(HfNode* node, int cnt, int vec_left[], string &s);	//��ӡ��������
	void destory(HfNode* node);	//���ٺ���
};

//////////////////////////////////////////////////////////////////////////////
// ���캯��
// �������ܣ������ַ��Լ�����Ƶ����ʼ����������
//����������arrayΪ�����ַ�������Ƶ�������飬szΪ���ֵ��ַ�����
//��������ֵ����
HfTree::HfTree(CntNode array[], int sz) {

	arr = array;		//��ʼ��arr
	size = sz;		//��ʼ��sz

	//����С�ѽ��л�������
	MinHeap* mh = new MinHeap(array, sz);

	HfNode* first;	
	HfNode* second;		
	HfNode* parent;
	while (mh->getLast()) {		//ѭ������Ϊ����Ԫ�ظ�������1
		mh->remove(first);	//��һ��ȡ��С
		mh->remove(second);	//�ڶ���ȡ��С
		parent = merge(first, second);	//���������кϲ�
		mh->insert(parent);		//��˫�׽����в���
	}
	mh->remove(parent);		//ȡ�������һ��Ԫ����Ϊ���������ĸ��ڵ�
	root = parent;
	root->parent = 0;

	encode(root);	//��ʼ��table����
}

//////////////////////////////////////////////////////////////////////////////
// ���캯��
// �������ܣ�����hfmTree.dat�ļ���ʼ����������
//������������
//��������ֵ����
HfTree::HfTree() {
	//��ȡ�ļ�����
	ifstream is;
	int sz = 0;		//szΪCntNode�����С
	is.open("hfmTree.dat", ios::binary | ios::in);
	is.read((char*)&(sz), sizeof(int));
	CntNode* array = new CntNode[sz];	//�����ڴ�ռ�
	for (int i = 0; i < sz; i++) {
		is.read((char*)&(array[i].letter), sizeof(char));
		is.read((char*)&(array[i].cont), sizeof(int));
	}
	is.close();
	//��ʼ��size��arr
	size = sz;
	arr = array;
	//������С�ѹ����������
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
	encode(root);	//��ʼ��table����
}

//////////////////////////////////////////////////////////////////////////////
// �ϲ�����
// �������ܣ����������ϲ�Ϊһ����������˫�׽��
//����������lΪ��ڵ㣬rΪ�ҽڵ�
//��������ֵ��parentΪ˫�׽��
HfNode* HfTree::merge(HfNode* l, HfNode* r) {

	HfNode* parent = new HfNode;
	//��˫�׽���Լ����ӽ����и�ֵ
	parent->left = l;
	parent->right = r;
	parent->cont = l->cont + r->cont;	//parent��ȨֵΪ����Ȩֵ���
	parent->parent = 0;
	l->parent = r->parent = parent;

	return parent;
}

//////////////////////////////////////////////////////////////////////////////
// Ҷ�ӽ����뺯��
// �������ܣ���Ҷ�ӽ����ַ����б���
//����������nodeΪҪ���б����Ҷ�ӽ��
//��������ֵ��sΪ���ַ���Ӧ������ַ���
string HfTree::encodeNode(HfNode* node) {

	myStack<HfNode*> ms;		//����һ��ջ
	HfNode* p = node;
	while (p) {		//���ý������ȴ�����������ѹջ
		ms.push(p);
		p = p->parent;
	}

	string s = "";		//sΪ��Ӧ������ַ���
	ms.pop(p);
	HfNode* follow;
	while (!ms.isEmpty()) {
		ms.pop(follow);
		//���ε�ջ����Ϊ���ӱ���Ϊ0
		if (follow == p->left) {
			s = s + '0';
		}
		//��Ϊ�Һ��ӱ���Ϊ1
		else if(follow==p->right){
			s = s + '1';
		}
		p = follow;
	}
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// ���뺯��
// �������ܣ���һ������Ҷ�ӽ����б���
//����������pΪ���ڵ�
//��������ֵ����
void HfTree::encode(HfNode* p) {
	if (p->left) {		//ѭ������������
		encode(p->left);
	}
	if (p->right) {
		encode(p->right);
	}
	//�����Ҷ�ӽ�㣬����б���
	if (p->left == 0 && p->right == 0) {
		int index = p->letter;
		table[index] = encodeNode(p);	//��Ҷ�ӽ�����Ľṹ����table����
	}
}

//////////////////////////////////////////////////////////////////////////////
// ���溯��
// �������ܣ����������������ļ�hfmTree.dat
//������������
//��������ֵ����
void HfTree::save() {
	ofstream os;
	os.open("hfmTree.dat", ios::binary);
	os.write((char*)&size, sizeof(int));		//�����ַ��Ķ���
	for (int i = 0; i < size; i++) {
		os.write((char*)&(arr[i].letter), sizeof(char));		//�����ַ�
		os.write((char*)&(arr[i].cont), sizeof(int));		//�������Ƶ��
	}
	os.close();
}

//////////////////////////////////////////////////////////////////////////////
// ת������
// �������ܣ������ַ��õ���Ӧ����
//����������cΪҪת�����ַ�
//��������ֵ��table[c]Ϊ��Ӧ�ı���
string HfTree::toCode(char c) {		
	return table[c];
}

//////////////////////////////////////////////////////////////////////////////
// ѹ������
// �������ܣ��������ַ������������ļ�
//����������sΪ�ַ���
//��������ֵ����
void HfTree::impress(string s) {
	
	string str = "";
	for (int i = 0; i < s.length(); i++) {	//��s���ȫ��0/1���ַ���������str
		str = str + table[s[i]];
	}
	//����str/8��str%8���õ�Ҫ��strת�ɶ��ٸ��ַ���length+1������Ҫ�����ٸ�'0'��rest��
	int length = str.length() / 8;
	int rest = str.length() % 8;
	for (int i = 0; i < 8 - rest; i++) {		//��'0',���ַ������ȴճ�8�ı���
		str = str + '0';
	}
	length++;

	ofstream os;
	os.open("codeFile.dat", ios::binary);
	//����length�Լ�rest
	os.write((char*)&(length), sizeof(int));
	os.write((char*)&(rest), sizeof(int));

	//���ַ�������unsigned char����
	for (int i = 0; i < length; i++) {

		string temp = str.substr(i * 8, 8);	//str��ÿ8λ����һ�ν�ȡ��ת��Ϊ��Ӧ���ַ�
		char s[8];
		for (int k = 0; k < 8; k++) {
			s[k] = temp[k];
		}

		unsigned char num = exchChar(s);		//���ַ���ת��ΪҪ�����ļ���unsigned char
		os.write((char*)&(num), sizeof(unsigned char));
	}
	os.close();
}

//////////////////////////////////////////////////////////////////////////////
// ת������
// �������ܣ����ַ���ת��ΪCntNode�������ڻ��������ĳ�ʼ��
//����������strΪҪ������ַ�����cont��¼�����˶������ַ�
//��������ֵ��arrΪ���ص�����
CntNode* strToCnt(string str, int& cont) {
	CntNode** letterArray = new CntNode * [128];
	for (int i = 0; i < 128; i++) {
		letterArray[i] = 0;
	}
	//ͳ���������ַ���
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
	//����CntNode����
	CntNode* arr = new CntNode[cont];
	int index = 0;
	for (int i = 0; i < 128; i++) {
		if (letterArray[i]) {	//����Ӧλ�ò�Ϊ�գ�����ӵ�������
			arr[index].cont = letterArray[i]->cont;
			arr[index].letter = letterArray[i]->letter;
			index++;
		}
	}
	return arr;
}

//////////////////////////////////////////////////////////////////////////////
// ���뺯��
// �������ܣ����������ļ����룬���ѽṹд���ļ�
//����������codeFileΪѹ���ļ���TextFileΪ�����д����ļ�
//��������ֵ����
void HfTree::decode(string codeFile, string TextFile) {
	ifstream is;
	int lenght = 0, rest = 0;
	//����ѹ���ļ���Ϣ
	is.open(codeFile, ios::binary | ios::in);
	is.read((char*)&(lenght), sizeof(int));
	is.read((char*)&(rest), sizeof(int));

	string str = "";
	//����Ϣ�����ַ���
	unsigned char num = 0;
	for (int i = 0; i < lenght; i++) {
		is.read((char*)&(num), sizeof(unsigned char));
		string temp = charToStr(num);	//�Ѷ�Ӧ��unsigned char����ת��Ϊ�ַ���
		str = str + temp;	//�����ַ�����ƴ��

	}
	str = str.substr(0, (lenght - 1) * 8 + rest);
	is.close();		//�ر���
	
	string text = "";	//�洢���������ַ���
	HfNode* p = root;	//��������������ָ��
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '0') {		//0������
			p = p->left;
		}
		else {		//����������
			p = p->right;
		}

		if (p->left == 0 && p->right == 0) {		//�����Ҷ�ӽ�����������
			text = text + (p->letter);
			p = root;
		}
	}
	ofstream os;
	os.open(TextFile);		//��������д���ļ�
	os << text;
	os.close();
}
//////////////////////////////////////////////////////////////////////////////
// ת������
// �������ܣ����ַ�����ת��Ϊunsigned char���͵��������ڴ洢
//����������arrΪҪת�����ַ�����
//��������ֵ��numΪҪ���д洢��unsigned char����
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
// ת������
// �������ܣ���unsigned char����ת��Ϊ��Ӧ���ַ���
//����������numΪҪ����ת��������
//��������ֵ��sΪnum��Ӧ���ַ���
string HfTree::charToStr(unsigned char num) {
	char str[9];
	for (int i = 0; i < 8; i++) {
		int temp = num % 2 + 48;		//��2ȡ��+48���õ���Ӧ�ַ���ascll��
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
// ��ӡ����
// �������ܣ�ֱ�۴�ӡ��������
//������������
//��������ֵ����
void HfTree::display() {

	int cnt = 0;
	int vec_left[130];		//����vec_left���飬���ڼ�¼ÿһ����Ҫ��ӡ��" "����
	HfNode* p = root;
	string s = "";

	for (int i = 0; i < 130; i++) {		//����ʼ��
		vec_left[i] = 1;
	}

	display(p, cnt, vec_left, s);	//���ý���ӡ����

	ofstream os;		//�������ַ���ʽд���ļ�
	os.open("treePrin.txt");
	os << s;
	os.close();
}
//////////////////////////////////////////////////////////////////////////////
// ����ӡ����
// �������ܣ���ӡ���������Ľ��
//����������nodeΪҪ��ӡ�Ľ�㣬cnt��vec_left��¼ÿ�д�ӡ" "��������sΪ��¼��ӡ������ַ���
//��������ֵ����
void HfTree::display(HfNode* node, int cnt, int vec_left[], string& s) {

	if (node != root) {		//������Ǹ���㣬��ӡ" "
		cout << " ";
		s = s + " ";
	}

	if (cnt > 0) {		//��ӡ���ж�Ӧ��" "��"| "��"|--"
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

	//��ΪҶ�ӽ�㣬��ӡ�ַ��Ͷ�Ӧ�ı���
	if (!node->left && !node->right) {
		cout<< node->letter << "-->" << table[node->letter] << endl;
		s = s + node->letter + "-->" + table[node->letter] + "\n";
		return;
	}
	else {		//������Ҷ�ӽ�㣬��ӡһ������
		cout << "��\n";
		s = s + "��\n";
	}

	if (node->left) {
		vec_left[cnt] = 1;
		display(node->left, cnt + 1, vec_left, s);	//��ӡ������
	}
	if (node->right) {
		vec_left[cnt] = 0;
		display(node->right, cnt + 1, vec_left, s);	//��ӡ������
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