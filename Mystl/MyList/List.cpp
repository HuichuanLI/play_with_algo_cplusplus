#include <iostream>
#include <list>
using namespace std;

//����Ľڵ�
template<typename T>
struct MyList_node {
  MyList_node<T> *prev;
  MyList_node<T> *next;
  T data;
};

//ͬʱ��������ͱ�͵�����������һ��
//������
template<typename T>
struct MyList_iterator {
  //���ͱ�
  typedef MyList_iterator<T> iterator;
  typedef MyList_node<T> *link_type;
  //�ڵ�ָ��
  link_type node;
  //���캯��
  MyList_iterator(link_type x) : node(x) {

  }
  MyList_iterator() : node(NULL) {

  }

  //����++��ʹ�����ǿ��Ի���¸��ڵ�ĵ�ַ
  iterator &operator++() {
    node = node->next;
    //���ر�����ͬʱָ����һ��
    return *this;
  }

  iterator &operator++(int) {
    //������������ǰ��ָ��ֵ
    iterator tmp = *this;
    //�������һ
    ++*this;
    //����δ��1ǰ�Ķ���
    return tmp;
  }

  iterator &operator--() {
    node = (node)->prev;
    return *this;
  }

  iterator &operator--(int) {
    iterator tmp = *this;
    --*this;
    return tmp;
  }

  iterator &operator=(iterator x) {
    node = x.node;
    return *this;
  }

  T &operator*() const {
    //���ؽڵ��������
    return node->data;
  }
};

//MyList
template<typename T>
class MyList {
 public:
  //�������ͱ�
  //��MyList<T>����Ϊ�ڲ�����Iterator
  typedef MyList_iterator<T> iterator;
 public:
  //���캯��
  MyList() : length(0) {
    node = new MyList_node<T>;
    node->next = node;
    node->prev = node;
  }

  ~MyList() {

  }
  //���������ͷ����
  iterator begin() {
    return node->next;

  }

  //���������β��ַ
  iterator end() {
    return node;
  }

  //push_front,push_back
  //�������ͷ����������
  void push_front(const T &x) {
    insert(begin(), x);
  }

  //�������β������
  void push_back(const T &x) {
    insert(end(), x);
  }

  void pop_front() {
    erase(begin());
  }

  void pop_back() {
    erase(--end());
  }

  iterator insert(const iterator &position, const T &x) {
    MyList_node<T> *tmp = new MyList_node<T>;
    tmp->data = x;
    tmp->prev = position.node->prev;
    tmp->next = position.node;
    position.node->prev->next = tmp;
    position.node->prev = tmp;
    ++length;
    return tmp;

  }

  void erase(const iterator &position) {
    position.node->prev->next = position.node->next;
    position.node->next->prev = position.node->prev;
    --length;
  }
 protected:
  MyList_node<T> *node;//�����ͷָ��
  size_t length;//������
};

//
int main(void) {

  MyList<int> mylist1;
  mylist1.push_front(10);
  mylist1.push_front(20);
  mylist1.push_front(30);

  MyList<int>::iterator iter;
  iter = mylist1.begin();
  cout << *iter << endl;
  cout << *++iter << endl;
  cout << *++iter << endl;
  cout << "___________________" << endl;
  mylist1.push_back(100);
  mylist1.push_back(200);
  mylist1.push_back(300);
  iter = mylist1.end();
  cout << *--iter << endl;
  cout << *--iter << endl;
  cout << *--iter << endl;
  cout << "__________" << endl;
  mylist1.pop_front();
  mylist1.pop_back();
  cout << *mylist1.begin() << endl;
  cout << *--mylist1.end() << endl;
  system("pause");
  return 0;
}
