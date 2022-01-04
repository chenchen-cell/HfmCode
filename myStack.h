//程序名：myStack.h
//程序功能：定义栈,用于树的遍历
//作者：陈宇权
//日期：2021.11.13
//版本：1.0
//修改内容：无
//修改日期：无
//修改作者：无
//
//


#pragma once
#include"Node.h"

template<class T>
class myStack {		//定义栈模板类
public:
	myStack():top(0) {}		//定义构造函数，top初始化为0
	~myStack();				//析构函数
	bool push(T d);			//压栈
	bool pop(T& d);			//弹栈，并将值付给d
	bool pop();				//弹栈
	bool isEmpty() { return top == 0; }		//判断栈是否为空
private:
	Node<T>* top;		//栈顶指针

};

//////////////////////////////////////////////////////////////////////////////
// 析构函数
// 函数功能：释放栈占用的内存空间
//函数参数：无
//参数返回值：无
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
// 压栈函数
// 函数功能：将数据压栈
//函数参数：d表示要进行压栈的元素
//参数返回值：true表示压栈成功，false表示压栈失败
template<class T>
bool myStack<T>::push(T d) {
	Node<T>* p = new Node<T>;
	if (p == 0)return false;
	p->data = d;
	p->next = top;
	//压栈成功则改变栈顶指针
	top = p;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// 弹栈函数
// 函数功能：将栈顶元素弹出
//函数参数：d接收要弹出的元素
//参数返回值：true表示弹栈成功，false表示弹栈失败
template<class T>
bool myStack<T>::pop(T& d) {
	//栈空则弹栈失败
	if (top == 0)return false;
	Node<T>* p = top;
	top = top->next;
	//将栈顶元素data赋值给d
	d = p->data;
	delete p;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// 弹栈函数
// 函数功能：将栈顶元素弹出
//函数参数：无
//参数返回值：true表示弹栈成功，false表示弹栈失败
template<class T>
bool myStack<T>::pop() {
	if (top == 0)return false;
	Node<T>* p = top;
	top = top->next;
	delete p;
	true;
}