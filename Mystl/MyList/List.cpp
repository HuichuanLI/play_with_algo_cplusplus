/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               创建：丁宋涛 夏曹俊，此代码可用作为学习参考                **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : C++泛型编程与STL开发实战
** Description   : winapi
** Contact       : xiacaojun@qq.com
**  博客   : http://blog.csdn.net/jiedichina
**	视频课程 : 网易云课堂	http://study.163.com/u/xiacaojun		
			   腾讯课堂		https://jiedi.ke.qq.com/				
			   csdn学院		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961	
**             51cto学院	http://edu.51cto.com/lecturer/index/user_id-12016059.html	
** 			   老夏课堂		http://www.laoxiaketang.com 
**                 
**   C++泛型编程与STL开发实战 课程群 ：725616972 加入群下载代码和交流
**   微信公众号  : jiedi2007
**		头条号	 : 夏曹俊
**
*******************************************************************************/
//！！！！！！！！！ 加C++泛型编程与STL开发实战  QQ群：725616972下载代码和交流//#include <iostream>
//#include <list>
//using namespace std;
//
////链表的节点
//template<typename T>
//struct MyList_node
//{
//	MyList_node<T> *prev;
//	MyList_node<T> *next;
//	T data;
//};
//
////同时将设计类型表和迭代器整合在一起
////迭代器
//template<typename T>
//struct MyList_iterator
//{
//	//类型表
//	typedef MyList_iterator<T> iterator;
//	typedef MyList_node<T>* link_type;
//	//节点指针
//	link_type node;
//	//构造函数
//	MyList_iterator(link_type x) :node(x) {
//
//	}
//	MyList_iterator() :node(NULL) {
//
//	}
//
//	//重载++，使得我们可以获得下个节点的地址
//	iterator& operator ++() {
//		node = node->next;
//		//返回本对象，同时指向下一个
//		return *this;
//	}
//
//	iterator& operator++(int) {
//		//保存自增运算前的指针值
//		iterator tmp = *this;
//		//本对象加一
//		++*this;
//		//返回未加1前的对象 
//		return tmp;
//	}
//
//	iterator& operator--() {
//		node = (node)->prev;
//		return *this;
//	}
//
//	iterator& operator--(int) {
//		iterator tmp = *this;
//		--*this;
//		return tmp;
//	}
//
//	iterator& operator=(iterator x) {
//		node = x.node;
//		return *this;
//	}
//
//	T& operator* () const {
//		//返回节点的数据域
//		return node->data;
//	}
//};
//
////MyList
//template<typename T>
//class MyList {
//public:
//	//数据类型表
//	//将MyList<T>声明为内部类型Iterator
//	typedef MyList_iterator<T> iterator;
//public:
//	//构造函数
//	MyList() :length(0) {
//		node = new MyList_node<T>;
//		node->next = node;
//		node->prev = node;
//	}
//	
//	~MyList()
//	{
//
//	}
//	//返回链表的头函数
//	iterator begin() {
//		return node->next;
//		
//	}
//
//	//返回链表的尾地址
//	iterator end() {
//		return node;
//	}
//
//	//push_front,push_back
//	//向链表的头部加入数据
//	void push_front(const T& x) {
//		insert(begin(), x);
//	}
//
//	//向链表的尾部插入
//	void push_back(const T& x) {
//		insert(end(), x);
//	}
//
//	void pop_front() {
//		erase(begin());
//	}
//
//	void pop_back() {
//		erase(--end());
//	}
//
//
//	iterator insert(const iterator& position, const T& x) {
//		MyList_node<T>* tmp = new MyList_node<T>;
//		tmp->data = x;
//		tmp->prev = position.node->prev;
//		tmp->next = position.node;
//		position.node->prev->next = tmp;
//		position.node->prev = tmp;
//		++length;
//		return tmp;
//
//	}
//
//	void erase(const iterator& position) {
//		position.node->prev->next = position.node->next;
//		position.node->next->prev = position.node->prev;
//		--length;
//	}
//protected:
//	MyList_node<T> *node;//链表的头指针
//	size_t length;//链表长度
//};
//
////
//int main(void){
//	
//	MyList<int> mylist1;
//	mylist1.push_front(10);
//	mylist1.push_front(20);
//	mylist1.push_front(30);
//
//	MyList<int>::iterator iter;
//	iter = mylist1.begin();
//	cout << *iter << endl;
//	cout << *++iter << endl;
//	cout << *++iter << endl;
//	cout << "___________________" << endl;
//	mylist1.push_back(100);
//	mylist1.push_back(200);
//	mylist1.push_back(300);
//	iter = mylist1.end();
//	cout << *--iter << endl;
//	cout << *--iter << endl;
//	cout << *--iter << endl;
//	cout << "__________" << endl;
//	mylist1.pop_front();
//	mylist1.pop_back();
//	cout << *mylist1.begin() << endl;
//	cout << *--mylist1.end() << endl;
//		system("pause");
//		return 0;
//}
