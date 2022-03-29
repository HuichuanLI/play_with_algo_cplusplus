#pragma once
template<class T,int n>
class Array {
public:
	Array();
	Array(int length);
	~Array();
	
	int size();
	T get(int num);
	T& operator[](int num);
	void set(T data, int num);
public:
	T *pt;
	//int n;//作为长度？
};
//n是定长的，所以数组一旦生成，不能变化
template<class T,int n>
Array<T, n>::Array() {
	this->pt = new T[n];
}

template<class T, int n>
Array<T, n>::Array(int length) {
	this->pt = new T[length];
}

template<class T, int n>
Array<T, n>::~Array() {
	delete[] this->pt;
}

template<class T, int n>
int Array<T, n>::size() {
	return n;
}

template<class T, int n>
T Array<T, n>::get(int num) {
	if (num >= n || num < 0) {
		//异常

	}
	else {
		return *(this->pt + num);
	}
}
template<class T, int n>
void Array<T, n>::set(T data, int num) {
	if (num < 0 || num >= n) {
		//异常
	}
	else
	{
		*(pt + num) = data;
	}
}

template<class T, int n>
T& Array<T, n>::operator [](int num) {
	if (num < 0 || num >= n) {

	}
	else {
		return *(pt + num);
	}
}