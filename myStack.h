//��������myStack.h
//�����ܣ�����ջ,�������ı���
//���ߣ�����Ȩ
//���ڣ�2021.11.13
//�汾��1.0
//�޸����ݣ���
//�޸����ڣ���
//�޸����ߣ���
//
//


#pragma once
#include"Node.h"

template<class T>
class myStack {		//����ջģ����
public:
	myStack():top(0) {}		//���幹�캯����top��ʼ��Ϊ0
	~myStack();				//��������
	bool push(T d);			//ѹջ
	bool pop(T& d);			//��ջ������ֵ����d
	bool pop();				//��ջ
	bool isEmpty() { return top == 0; }		//�ж�ջ�Ƿ�Ϊ��
private:
	Node<T>* top;		//ջ��ָ��

};

//////////////////////////////////////////////////////////////////////////////
// ��������
// �������ܣ��ͷ�ջռ�õ��ڴ�ռ�
//������������
//��������ֵ����
template<class T>
myStack<T>::~myStack() {
	Node<T>* p;
	while (top) {
		p = top->next;
		delete top;
		top = p;
	}
}

//////////////////////////////////////////////////////////////////////////////
// ѹջ����
// �������ܣ�������ѹջ
//����������d��ʾҪ����ѹջ��Ԫ��
//��������ֵ��true��ʾѹջ�ɹ���false��ʾѹջʧ��
template<class T>
bool myStack<T>::push(T d) {
	Node<T>* p = new Node<T>;
	if (p == 0)return false;
	p->data = d;
	p->next = top;
	//ѹջ�ɹ���ı�ջ��ָ��
	top = p;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// ��ջ����
// �������ܣ���ջ��Ԫ�ص���
//����������d����Ҫ������Ԫ��
//��������ֵ��true��ʾ��ջ�ɹ���false��ʾ��ջʧ��
template<class T>
bool myStack<T>::pop(T& d) {
	//ջ����ջʧ��
	if (top == 0)return false;
	Node<T>* p = top;
	top = top->next;
	//��ջ��Ԫ��data��ֵ��d
	d = p->data;
	delete p;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// ��ջ����
// �������ܣ���ջ��Ԫ�ص���
//������������
//��������ֵ��true��ʾ��ջ�ɹ���false��ʾ��ջʧ��
template<class T>
bool myStack<T>::pop() {
	if (top == 0)return false;
	Node<T>* p = top;
	top = top->next;
	delete p;
	true;
}