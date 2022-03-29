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
//！！！！！！！！！ 加C++泛型编程与STL开发实战  QQ群：725616972下载代码和交流
//#include <iostream>
//#include <vector>
//using namespace std;
//
////MyVector的类模板
//template<typename Ty>
//class MyVector {
//public:
//	//内嵌类型表
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
//			cout << "越界" << endl;
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
//			cout << "取值错误" << endl;
//		}
//	}
//
//	//数组的头指针
//	viter begin() {
//		return star;
//	}
//
//	viter end() {
//		return star + finish;
//	}
//protected:
//	viter m_Data;//数组头指针
//	int m_nLen;//数组长度
//	viter star;//数组的起始地址
//	int finish;//数组的满位标志
//	int end_of_element;//数组的末尾标识
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