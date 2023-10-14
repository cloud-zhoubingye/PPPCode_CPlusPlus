//
// Created by Zhou on 2023/2/25.
//
/*
 * VECTOR3.0
 *
 * 支持七大功能特性
 * 一，拥有默认构造函数，解决漏掉初始化的麻烦
 * 二，拥有接受一个参数或参数列表的构造函数
 * 三，拥有拷贝构造函数和拷贝赋值操作，实现深拷贝，避免内存泄漏和重复释放
 * 四，拥有移动构造函数和移动赋值操作，内存消耗低且运行速度快
 * 五，单参数构造函数均为更安全的显式限定，避免隐式类型转换
 * 六，支持[]取下标操作进行值的访问与修改，支持[]对const VECTOR进行值的访问
 * 七，拥有析构函数，避免内存泄漏
 */
#include <algorithm>
#include <iostream>
using namespace std;
class  VECTOR
{
private:
    int size_of_vector;      //大小
    double* elements;     //指向元素的指针
public:
    int size()const;
    explicit VECTOR(int length);    //构造函数
    VECTOR(initializer_list<double>list);       //初始化器列表构造函数
    explicit VECTOR(const VECTOR&arg);    //拷贝构造函数
    VECTOR& operator=(const VECTOR&arg);        //拷贝赋值函数
    explicit VECTOR(VECTOR&&arg);        //移动构造函数
    VECTOR& operator=(VECTOR&&arg);      //移动赋值
    double& operator[](int n);      //读写元素
    double operator[](int n)const;      //读取const VECTOR中的元素
    ~VECTOR();       //析构函数
};
int VECTOR::size()const
{
    return size_of_vector;
}
VECTOR::VECTOR(int length)    //构造函数
        :size_of_vector{length},elements{new double[length]}
{
    for (int i = 0; i < size_of_vector; ++i){
        elements[i] = 0.0;      //初始化
    }
}
VECTOR::VECTOR(initializer_list<double>list)     //初始化器列表构造函数
        :size_of_vector{static_cast<int>(list.size())},elements{new double[size_of_vector]}
{
    copy(list.begin(),list.end(),elements);
}
VECTOR::VECTOR(const VECTOR&arg)    //拷贝构造函数
        :size_of_vector{arg.size_of_vector},elements{new double[size_of_vector]}
{
    copy(arg.elements,arg.elements+arg.size_of_vector,elements);
}
VECTOR& VECTOR::operator=(const VECTOR&arg)        //拷贝赋值操作
{
    size_of_vector=arg.size_of_vector;      //拷贝vector大小
    double*p_elem=new double[size_of_vector];       //申请存储数据的新空间
    copy(arg.elements,arg.elements+arg.size_of_vector,p_elem);      //拷贝数组到存储数据的新空间
    delete[] elements;        //释放旧空间
    elements=p_elem;        //使原数组指向存储数据的新空间
    return *this;       //返回vector的自引用
}
VECTOR::VECTOR(VECTOR&&arg)        //移动构造函数
        :size_of_vector{arg.size_of_vector},elements{arg.elements}
{
    arg.size_of_vector=0;
    arg.elements= nullptr;      //还没有分配，所以无需delete，直接置空即可
}
VECTOR& VECTOR::operator=(VECTOR &&arg)      //移动赋值操作
{
    size_of_vector=arg.size_of_vector;      //拷贝size
    delete[] elements;      //释放待移动到的对象的旧空间
    elements=arg.elements;      //把待移动到的对象的element指向原对象的
    arg.elements= nullptr;      //改变原对象的element指向
    arg.size_of_vector=0;       //将原对象的size改为0
    return *this;
}
double& VECTOR::operator[](int n)       //读写元素
{
    return elements[n];
}
double VECTOR::operator[](int n)const      //读取const VECTOR中的元素
{
    return elements[n];
}
VECTOR::~VECTOR()       //析构函数
{
    delete[] elements;
}
