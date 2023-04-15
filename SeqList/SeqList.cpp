#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

#define InitSize 10   //动态数组的初始尺寸
#define IncSize  5    //当动态数组存满数据后每次扩容所能多保存的数据元素数量

template<typename T> //T代表数组中元素的类型
class SeqList {
public:
    SeqList(int length = InitSize); //构造函数，参数可以有默认值
    ~SeqList();                   //析构函数

public:
    bool ListInsert(int i, const T &e);  //在第i个位置插入指定元素e
    bool ListDelete(int i);              //删除第i个位置的元素
    bool GetElem(int i, T &e);           //获得第i个位置的元素值
    int LocateElem(const T &e);         //按元素值查找其在顺序表中第一次出现的位置

    void DispList();                     //输出顺序表中的所有元素
    int ListLength();                   //获取顺序表的长度
    void ReverseList();                  //翻转顺序表

private:
    void IncreaseSize();         //当顺序表存满数据后可以调用此函数为顺序表扩容

private:
    T *m_data;                   //存放顺序表中的元素
    int m_length;                 //顺序表当前长度（当前有几个元素）
    int m_maxsize;                //动态数组最大容量
};

//通过构造函数对顺序表进行初始化
template<typename T>
SeqList<T>::SeqList(int length) {
    m_data = new T[length]; //为一维数组动态分配内存
    m_length = 0;           //顺序表当前实际长度为0，表示还未向其中存入任何数据元素
    m_maxsize = length;     //顺序表最多可以存储m_maxsize个数据元素
}

//通过析构函数对顺序表进行资源释放
template<typename T>
SeqList<T>::~SeqList() {
    delete[] m_data;
    m_length = 0; //非必须
}

//在第i个位置（位置编号从1开始）插入指定元素e，时间复杂度：O(n)，时间开销主要源于元素的移动
template<typename T>
bool SeqList<T>::ListInsert(int i, const T &e) {
    //如果顺序表已经存满了数据，则不允许再插入新数据了
    if (m_length >= m_maxsize) {
        //cout << "顺序表已满，不能再进行插入操作了!" << endl;
        //return false;
        IncreaseSize();
    }

    //判断插入位置i是否合法，i的合法值应该是1到m_length+1之间
    if (i < 1 || i > (m_length + 1)) {
        cout << "元素" << e << "插入的位置" << i << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
        return false;
    }

    //从最后一个元素开始向前遍历到要插入新元素的第i个位置，分别将这些位置中原有的元素向后移动一个位置
    for (int j = m_length; j >= i; --j) {
        m_data[j] = m_data[j - 1];
    }
    m_data[i - 1] = e;   //在指定位置i处插入元素e，因为数组下标从0开始，所以这里用i-1表示插入位置所对应的数组下标
    cout << "成功在位置为" << i << "处插入元素" << m_data[i - 1] << "!" << endl;
    m_length++;        //实际表长+1
    return true;
}

//删除第i个位置的元素
template<typename T>
bool SeqList<T>::ListDelete(int i) {
    if (m_length < 1) {
        cout << "当前顺序表为空，不能删除任何数据!" << endl;
        return false;
    }
    if (i < 1 || i > m_length) {
        cout << "删除的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }
    cout << "成功删除位置为" << i << "的元素，该元素的值为" << m_data[i - 1] << "!" << endl;
    //从数组中第i+1个位置开始向后遍历所有元素，分别将这些位置中原有的元素向前移动一个位置
    for (int j = i; j < m_length; ++j) {
        m_data[j - 1] = m_data[j];
    }
    m_length--;       //实际表长-1
    return true;
}

//获得第i个位置的元素值
template<class T>
bool SeqList<T>::GetElem(int i, T &e) //参数e是引用类型参数，确保将该值带回调用者
{
    if (m_length < 1) {
        cout << "当前顺序表为空，不能获取任何数据!" << endl;
        return false;
    }

    if (i < 1 || i > m_length) {
        cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }
    e = m_data[i - 1];
    cout << "成功获取位置为" << i << "的元素，该元素的值为" << m_data[i - 1] << "!" << endl;
    return true;
}

//按元素值查找其在顺序表中第一次出现的位置
template<class T>
int SeqList<T>::LocateElem(const T &e) {
    for (int i = 0; i < m_length; ++i) {
        if (m_data[i] == e) {
            cout << "值为" << e << "的元素在顺序表中第一次出现的位置为" << i + 1 << "!" << endl;
            return i + 1;  //返回的位置应该用数组下标值+1
        }
    }
    cout << "值为" << e << "的元素在顺序表中没有找到!" << endl;
    return -1;  //返回-1表示查找失败
}

//输出顺序表中的所有元素，时间复杂度为O(n)
template<class T>
void SeqList<T>::DispList() {
    for (int i = 0; i < m_length; ++i) {
        cout << m_data[i] << " ";  //每个数据之间以空格分隔
    }
    cout << endl; //换行
}

//获取顺序表的长度，时间复杂度为O(1)
template<class T>
int SeqList<T>::ListLength() {
    return m_length;
}

//翻转顺序表，时间复杂度为O(n)
template<class T>
void SeqList<T>::ReverseList() {
    if (m_length <= 1) {
        //如果顺序表中没有元素或者只有一个元素，那么就不用做任何操作
        return;
    }
    T temp;
    for (int i = 0; i < m_length / 2; ++i) {
        temp = m_data[i];
        m_data[i] = m_data[m_length - i - 1];
        m_data[m_length - i - 1] = temp;
    }
}

//当顺序表存满数据后可以调用此函数为顺序表扩容，时间复杂度为O(n)
template<class T>
void SeqList<T>::IncreaseSize() {
    T *p = m_data;
    m_data = new T[m_maxsize + IncSize]; //重新为顺序表分配更大的内存空间
    for (int i = 0; i < m_length; i++) {
        m_data[i] = p[i];                //将数据复制到新区域
    }
    m_maxsize = m_maxsize + IncSize;     //顺序表最大长度增加IncSize
    delete[] p;                          //释放原来的内存空间
}

int main() {

    SeqList<int> seqobj(10);

    seqobj.ListInsert(1, 15);
    seqobj.ListInsert(2, 10);
    seqobj.ListInsert(30, 8);

    seqobj.ListDelete(1);

    int eval = 0;
    seqobj.GetElem(1, eval); //如果GetElem()返回true，则eval中保存着获取到的元素值

    int findvalue = 10; //在顺序表中要找的元素值
    seqobj.LocateElem(findvalue);

    seqobj.ListInsert(2, 100);
    seqobj.DispList();
    cout << seqobj.ListLength() << endl;
    seqobj.ReverseList();
    seqobj.DispList();

    for (int i = 3; i < 30; ++i) {
        seqobj.ListInsert(i, i * 2);
    }
    seqobj.DispList();

    return 0;
}