//��������MinHeap.h
//�����ܣ�������С��,���ڹ�����������
//���ߣ�����Ȩ
//���ڣ�2021.12.3
//�汾��1.0
//�޸����ݣ���
//�޸����ڣ���
//�޸����ߣ���
//
//

#pragma once

//����Ȩֵ�ṹ����¼�ַ��Ͷ�Ӧ��Ƶ��
struct CntNode {		
	char letter;		//�ַ�
	int cont;		//�ַ����ֵ�Ƶ��
};
//��������������ṹ��
struct HfNode
{
	char letter;		//�ַ�
	int cont;	//Ƶ��
	HfNode* left, * right, * parent;		//���Һ��Ӻ͸�ĸָ��
	//���캯��
	HfNode() :letter('\0'), cont(0), left(0), right(0), parent(0) {}
	//���캯��
	HfNode(char c, int num, HfNode* l, HfNode* r, HfNode* p) :letter(c), cont(num), left(l), right(r), parent(p) {}
};

//////////////////////////////////////////////////////////////////////////////
// ת������
// �������ܣ�����CntNode�ṹת����Ӧ��HfNode�ṹ
//����������nodeΪ��Ҫ����ת���Ľ��
//��������ֵ��pΪת����Ľ��
HfNode* exNode(CntNode node) {
	HfNode* p = new HfNode(node.letter, node.cont, 0, 0, 0);
	return p;
}


class MinHeap {		//������С����
public:
	MinHeap(int size = 100);		//���캯��
	MinHeap(HfNode* array[], int size);		//���캯��
	MinHeap(CntNode a[], int size);		//���캯��
	~MinHeap() { delete[] arr; }		//��������
	bool insert(HfNode* node);		//����
	bool remove(HfNode *&x);		//ɾ����С������
	bool isEmpty() { return last == -1; }	//�п�
	bool isFull() { return last == maxsize-1; }		//����
	int getLast() { return last; }		//��ȡ�������Ԫ�ص��±�
private:
	HfNode** arr;	//������������ָ������
	int maxsize;		//�����������
	int last;		//���Ԫ�ص��±�
	void siftUp(int start);		//���ϵ���
	void siftDown();		//���µ���
};
//////////////////////////////////////////////////////////////////////////////
// ���캯��
// �������ܣ���ʼ��ָ������arr���������maxsize�����Ԫ���±�last
//����������sizeΪ�����С
//��������ֵ����
MinHeap::MinHeap(int size) {
	arr = new HfNode*[size];
	last = -1;		
	maxsize = size;
}

//////////////////////////////////////////////////////////////////////////////
// ���캯��
// �������ܣ���ʼ��ָ������arr���������maxsize�����Ԫ���±�last
//����������arrayΪ��Ҫ���д����HfNode*���飬sizeΪ�����С
//��������ֵ����
MinHeap::MinHeap(HfNode* array[], int size) {	
	maxsize =  size + 5;
	arr = new HfNode*[maxsize];		//�����ڴ�ռ�
	last = -1;
	for (int i = 0; i < size; i++) {		//���ν�����С�ѵĲ���
		insert(array[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////
// ���캯��
// �������ܣ���ʼ��ָ������arr���������maxsize�����Ԫ���±�last
//����������aΪ��Ҫ���д����CntNode���飬sizeΪ�����С
//��������ֵ����
MinHeap::MinHeap(CntNode a[], int size) {
	maxsize = size + 5;
	arr = new HfNode * [maxsize];	//�����ڴ�ռ�
	last = -1;
	for (int i = 0; i < size; i++) {		//���ν���Ԫ�ص����
		HfNode*p = exNode(a[i]);		//��ת��Ϊ��Ӧ��HfNode*
		insert(p);		//���в���
	}
}

//////////////////////////////////////////////////////////////////////////////
// ���ϵ�������
// �������ܣ���ָ��λ�ý�����С�ѵ����ϵ���
//����������startΪҪ��ʼ�������ϵ�����λ��
//��������ֵ����
void MinHeap::siftUp(int start) {

	int temp = start;
	int p = (start - 1) / 2;		//pΪstart��˫��
	while (temp>0) {	//�������ϵ���ֱ��������ڵ�
		if (arr[p]->cont < arr[temp]->cont)break;	//���������С�ѵ�������ѭ������
		//��������������е���
		HfNode* node = arr[p];		
		arr[p] = arr[temp];
		arr[temp] = node;
		//�ı�temp��p��ֵ���������ϵ���
		temp = p;	
		p = (p - 1) / 2;
	}
}

//////////////////////////////////////////////////////////////////////////////
// ���µ�������
// �������ܣ��Ӹ���㿪ʼ�������µ�����ֱ���������Ԫ���±�
//������������
//��������ֵ����
void MinHeap::siftDown() {

	int p = 0;	//pΪ˫�ף��Ӹ��ڵ�0��ʼ���е���
	int i = 2 * p + 1;	//iΪp������
	while (i<=last)
	{
		int l = i;	//lΪ�����±�
		int r = l + 1;	//rΪ�Һ����±�
		int temp = l;	//tempΪҪ���е������±꣬��Ϊi
		if (r <= last) {		//�Ƚ�temp�Ƿ���Ҫ����Ϊr
			if (arr[r]->cont < arr[l]->cont)temp = r;
		}
		//������С�Ѷ�������ֹѭ��
		if (arr[p]->cont < arr[temp]->cont)break;
		//�������ֵ�Ľ���
		HfNode* node = arr[p];
		arr[p] = arr[temp];
		arr[temp] = node;
		//�ı�p��i��ֵ�������������µ���
		p = temp;
		i = 2 * p + 1;
	}
}

//////////////////////////////////////////////////////////////////////////////
// ���뺯��
// �������ܣ�����С�ѽ���Ԫ�ز���
//����������nodeΪҪ����Ļ��������
//��������ֵ��true��ʾ����ɹ���false��ʾ����ʧ��
bool MinHeap::insert(HfNode* node) {
	if (isFull())return false;	//����������ʧ��
	last++;		//���Ԫ���±�+1
	arr[last] = node;
	siftUp(last);	//�������ϵ���
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// ɾ������
// �������ܣ�ɾ�������
//����������x����Ҫɾ���Ľ��
//��������ֵ��true��ʾɾ���ɹ���false��ʾɾ��ʧ��
bool MinHeap::remove(HfNode *&x) {
	if (isEmpty())return false;		//�ѿ���ɾ��ʧ��
	x = arr[0];		//��x���и�ֵ
	arr[0] = arr[last];
	last--;		//���Ԫ���±�-1
	siftDown();	//���µ���
	return true;
}
