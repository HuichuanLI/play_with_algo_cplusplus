
#include <iostream>
#include <vector>
using namespace std;

//MyVector����ģ��
template<typename Ty>
class MyVector {
public:
	typedef Ty value;
	typedef Ty* viter;
public:
	MyVector(int nLen = 0) :m_nLen(nLen), m_Data(NULL), finish(0) {
		if (nLen > 0) {
			m_Data = new Ty[nLen];
			star = m_Data;
			end_of_element = nLen;
		}
	}
	~MyVector()
	{
		delete[] m_Data;
	}
	void push_back(const value& x) {
		if (end_of_element != finish) {
			*(star + finish) = x;
			++finish;
		}
		else {
			cout << "空了" << endl;
		}
	}

   value pop_back() {
		--finish;
		//return *(star + finish);
	}

	value& operator[](int n) {
		if(n==finish || n<finish){
			return *(star + n);
		}
		else {
			cout << "ȡֵ����" << endl;
		}
	}

	viter begin() {
		return star;
	}

	viter end() {
		return star + finish;
	}
protected:
	viter m_Data;//����ͷָ��
	int m_nLen;//���鳤��
	viter star;//�������ʼ��ַ
	int finish;//�������λ��־
	int end_of_element;//�����ĩβ��ʶ
};

int main() {
	/*int x;
	MyVector<int> vec(10);
	vec.push_back(100);
	vec.push_back(200);
	vec.push_back(300);
	x = vec.pop_back();
	cout << "x=" << x << endl;
	cout << vec[0] << endl;
	cout << vec[1] << endl;*/

	MyVector<int> v1(10);
	cout << v1.begin() << " " << v1.end() << endl;

	/*/vector<int> myVec;
	myVec.begin();
	vector<int>::iterator iter = myVec.begin();*/
	MyVector<int>::viter iter;
	v1.push_back(100);
	v1.push_back(200);
	v1.push_back(300);
	for (iter = v1.begin();iter < v1.end();iter++) {
		cout << *iter << endl;
	}
	return 0;
}