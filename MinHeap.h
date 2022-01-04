//程序名：MinHeap.h
//程序功能：定义最小堆,用于构建霍夫曼树
//作者：陈宇权
//日期：2021.12.3
//版本：1.0
//修改内容：无
//修改日期：无
//修改作者：无
//
//

#pragma once

//定义权值结构，记录字符和对应的频数
struct CntNode {		
	char letter;		//字符
	int cont;		//字符出现的频数
};
//定义霍夫曼树结点结构体
struct HfNode
{
	char letter;		//字符
	int cont;	//频数
	HfNode* left, * right, * parent;		//左右孩子和父母指针
	//构造函数
	HfNode() :letter('\0'), cont(0), left(0), right(0), parent(0) {}
	//构造函数
	HfNode(char c, int num, HfNode* l, HfNode* r, HfNode* p) :letter(c), cont(num), left(l), right(r), parent(p) {}
};

//////////////////////////////////////////////////////////////////////////////
// 转换函数
// 函数功能：根据CntNode结构转换对应的HfNode结构
//函数参数：node为需要进行转换的结点
//参数返回值：p为转换后的结点
HfNode* exNode(CntNode node) {
	HfNode* p = new HfNode(node.letter, node.cont, 0, 0, 0);
	return p;
}


class MinHeap {		//定义最小堆类
public:
	MinHeap(int size = 100);		//构造函数
	MinHeap(HfNode* array[], int size);		//构造函数
	MinHeap(CntNode a[], int size);		//构造函数
	~MinHeap() { delete[] arr; }		//析构函数
	bool insert(HfNode* node);		//插入
	bool remove(HfNode *&x);		//删除最小（根）
	bool isEmpty() { return last == -1; }	//判空
	bool isFull() { return last == maxsize-1; }		//判满
	int getLast() { return last; }		//获取数组最后元素的下标
private:
	HfNode** arr;	//霍夫曼树结点的指针数组
	int maxsize;		//数组最低容量
	int last;		//最后元素的下标
	void siftUp(int start);		//向上调整
	void siftDown();		//向下调整
};
//////////////////////////////////////////////////////////////////////////////
// 构造函数
// 函数功能：初始化指针数组arr、最大容量maxsize、最后元素下标last
//函数参数：size为数组大小
//参数返回值：无
MinHeap::MinHeap(int size) {
	arr = new HfNode*[size];
	last = -1;		
	maxsize = size;
}

//////////////////////////////////////////////////////////////////////////////
// 构造函数
// 函数功能：初始化指针数组arr、最大容量maxsize、最后元素下标last
//函数参数：array为需要进行处理的HfNode*数组，size为数组大小
//参数返回值：无
MinHeap::MinHeap(HfNode* array[], int size) {	
	maxsize =  size + 5;
	arr = new HfNode*[maxsize];		//申请内存空间
	last = -1;
	for (int i = 0; i < size; i++) {		//依次进行最小堆的插入
		insert(array[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////
// 构造函数
// 函数功能：初始化指针数组arr、最大容量maxsize、最后元素下标last
//函数参数：a为需要进行处理的CntNode数组，size为数组大小
//参数返回值：无
MinHeap::MinHeap(CntNode a[], int size) {
	maxsize = size + 5;
	arr = new HfNode * [maxsize];	//申请内存空间
	last = -1;
	for (int i = 0; i < size; i++) {		//依次进行元素的添加
		HfNode*p = exNode(a[i]);		//将转换为对应的HfNode*
		insert(p);		//进行插入
	}
}

//////////////////////////////////////////////////////////////////////////////
// 向上调整函数
// 函数功能：从指定位置进行最小堆的向上调整
//函数参数：start为要开始进行向上调整的位置
//参数返回值：无
void MinHeap::siftUp(int start) {

	int temp = start;
	int p = (start - 1) / 2;		//p为start的双亲
	while (temp>0) {	//依次向上调整直到到达根节点
		if (arr[p]->cont < arr[temp]->cont)break;	//如果满足最小堆的条件，循环结束
		//不满足条件则进行调整
		HfNode* node = arr[p];		
		arr[p] = arr[temp];
		arr[temp] = node;
		//改变temp和p的值，继续向上调整
		temp = p;	
		p = (p - 1) / 2;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 向下调整函数
// 函数功能：从根结点开始进行向下调整，直到超过最后元素下标
//函数参数：无
//参数返回值：无
void MinHeap::siftDown() {

	int p = 0;	//p为双亲，从根节点0开始进行调整
	int i = 2 * p + 1;	//i为p的左孩子
	while (i<=last)
	{
		int l = i;	//l为左孩子下标
		int r = l + 1;	//r为右孩子下标
		int temp = l;	//temp为要进行调整的下标，设为i
		if (r <= last) {		//比较temp是否需要更改为r
			if (arr[r]->cont < arr[l]->cont)temp = r;
		}
		//符合最小堆定义则终止循环
		if (arr[p]->cont < arr[temp]->cont)break;
		//否则进行值的交换
		HfNode* node = arr[p];
		arr[p] = arr[temp];
		arr[temp] = node;
		//改变p和i的值，继续进行向下调整
		p = temp;
		i = 2 * p + 1;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 插入函数
// 函数功能：向最小堆进行元素插入
//函数参数：node为要插入的霍夫曼结点
//参数返回值：true表示插入成功，false表示插入失败
bool MinHeap::insert(HfNode* node) {
	if (isFull())return false;	//堆满，插入失败
	last++;		//最后元素下标+1
	arr[last] = node;
	siftUp(last);	//进行向上调整
	return true;
}

//////////////////////////////////////////////////////////////////////////////
// 删除函数
// 函数功能：删除根结点
//函数参数：x保存要删除的结点
//参数返回值：true表示删除成功，false表示删除失败
bool MinHeap::remove(HfNode *&x) {
	if (isEmpty())return false;		//堆空则删除失败
	x = arr[0];		//对x进行赋值
	arr[0] = arr[last];
	last--;		//最后元素下标-1
	siftDown();	//向下调整
	return true;
}
