/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               ������������ �Ĳܿ����˴��������Ϊѧϰ�ο�                **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : C++���ͱ����STL����ʵս
** Description   : winapi
** Contact       : xiacaojun@qq.com
**  ����   : http://blog.csdn.net/jiedichina
**	��Ƶ�γ� : �����ƿ���	http://study.163.com/u/xiacaojun		
			   ��Ѷ����		https://jiedi.ke.qq.com/				
			   csdnѧԺ		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961	
**             51ctoѧԺ	http://edu.51cto.com/lecturer/index/user_id-12016059.html	
** 			   ���Ŀ���		http://www.laoxiaketang.com 
**                 
**   C++���ͱ����STL����ʵս �γ�Ⱥ ��725616972 ����Ⱥ���ش���ͽ���
**   ΢�Ź��ں�  : jiedi2007
**		ͷ����	 : �Ĳܿ�
**
*******************************************************************************/
//������������������ ��C++���ͱ����STL����ʵս  QQȺ��725616972���ش���ͽ���
//#include <iostream>
//#include <vector>
//using namespace std;
//
////MyVector����ģ��
//template<typename Ty>
//class MyVector {
//public:
//	//��Ƕ���ͱ�
//	typedef Ty value;
//	typedef Ty* viter;
//public:
//	MyVector(int nLen = 0) :m_nLen(nLen), m_Data(NULL), finish(0) {
//		if (nLen > 0) {
//			m_Data = new Ty[nLen];
//			star = m_Data;
//			end_of_element = nLen;
//		}
//	}
//	~MyVector()
//	{
//		delete[] m_Data;
//	}
//	void push_back(const value& x) {
//		if (end_of_element != finish) {
//			*(star + finish) = x;
//			++finish;
//		}
//		else {
//			cout << "Խ��" << endl;
//		}
//	}
//
//   value pop_back() {
//		--finish;
//		//return *(star + finish);
//	}
//
//	value& operator[](int n) {
//		if(n==finish || n<finish){
//			return *(star + n);
//		}
//		else {
//			cout << "ȡֵ����" << endl;
//		}
//	}
//
//	//�����ͷָ��
//	viter begin() {
//		return star;
//	}
//
//	viter end() {
//		return star + finish;
//	}
//protected:
//	viter m_Data;//����ͷָ��
//	int m_nLen;//���鳤��
//	viter star;//�������ʼ��ַ
//	int finish;//�������λ��־
//	int end_of_element;//�����ĩβ��ʶ
//};
//
//int main() {
//	/*int x;
//	MyVector<int> vec(10);
//	vec.push_back(100);
//	vec.push_back(200);
//	vec.push_back(300);
//	x = vec.pop_back();
//	cout << "x=" << x << endl;
//	cout << vec[0] << endl;
//	cout << vec[1] << endl;*/
//
//	MyVector<int> v1(10);
//	cout << v1.begin() << " " << v1.end() << endl;
//
//	/*/vector<int> myVec;
//	myVec.begin();
//	vector<int>::iterator iter = myVec.begin();*/
//	MyVector<int>::viter iter;
//	v1.push_back(100);
//	v1.push_back(200);
//	v1.push_back(300);
//	for (iter = v1.begin();iter < v1.end();iter++) {
//		cout << *iter << endl;
//	}
//	system("pause");
//	return 0;
//}