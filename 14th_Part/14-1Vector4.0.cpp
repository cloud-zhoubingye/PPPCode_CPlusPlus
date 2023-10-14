//
// Created by Zhou on 2023/2/27.
//
#include "../Head/std_lib_facilities.h"
/*
 * VECTOR4.0
 * 支持十大功能特性
 * 一，拥有默认构造函数，解决漏掉初始化的麻烦
 * 二，拥有接受一个参数或参数列表的构造函数
 * 三，拥有拷贝构造函数和拷贝赋值操作，实现深拷贝，避免内存泄漏和重复释放
 * 四，对于自赋值以及空间足够的赋值，有效避免了不必要的内存分配与释放
 * 五，拥有移动构造函数和移动赋值操作，内存消耗低且运行速度快
 * 六，单参数构造函数均为更安全的显式限定，避免隐式类型转换
 * 七，支持[]取下标操作进行值的访问与修改，支持[]对const VECTOR进行值的访问
 * 八，允许用户知晓已用空间和预留空间的大小，并改变已用空间或增加预留空间
 * 九，支持push_back操作，同时以加倍式内存扩张战略减少反复复制的过程
 * 十，拥有析构函数，避免内存泄漏
 */
#include <algorithm>
#include <iostream>
using namespace std;
class  VECTOR
{
private:
    int size_of_vector;      //大小
    int size_of_free_space;      //空闲空间
    double* elements;     //指向元素的指针
public:
    int size()const;

    [[maybe_unused]] explicit VECTOR(int length=0);    //构造函数
    VECTOR(initializer_list<double>list);       //初始化器列表构造函数
    VECTOR(const VECTOR&arg);    //拷贝构造函数
    VECTOR& operator=(const VECTOR&arg);        //拷贝赋值函数
    VECTOR(VECTOR&&arg);        //移动构造函数
    VECTOR& operator=(VECTOR&&arg);      //移动赋值
    double& operator[](int n);      //读写元素
    double operator[](int n)const;      //读取const VECTOR中的元素
    void reverse(int new_allocate);     //增加预留空间
    int capacity()const;        //返回预留空间大小
    void resize(int new_size);      //重设大小
    void push_back(double data);        //放入新元素
    ~VECTOR();       //析构函数
};
int VECTOR::size()const
{
    return size_of_vector;
}

[[maybe_unused]] VECTOR::VECTOR(int length)    //构造函数
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
    copy(arg.elements,arg.elements+arg.size_of_vector-1,elements);
}
VECTOR& VECTOR::operator=(const VECTOR&arg)        //拷贝赋值操作
{
    if (&arg==this){        //如果是自赋值
        return *this;
    }
    if (size_of_free_space>=arg.size_of_vector)     //如果空间足够
    {
        copy(arg.elements,arg.elements+size_of_vector-1,elements);
        size_of_vector=arg.size_of_vector;
        return *this;
    }
    size_of_free_space=size_of_vector=arg.size_of_vector;      //拷贝vector大小
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
int VECTOR::capacity()const         //返回预留空间大小
{
    return size_of_free_space;
}
void VECTOR::reverse(int new_allocate)      //增加预留空间
{
    if (new_allocate<=size_of_free_space) return;        //空间已经足够用
    double* p=new double[new_allocate];        //重新分配空间
    copy(elements,elements+size_of_vector-1,p);     //复制原有元素
    delete[] p;
    elements=p;
    size_of_free_space=new_allocate;     //刷新空闲空间大小
}
void VECTOR::resize(int new_size)       //重设大小
{
    reverse(new_size);      //申请足够的大小
    for (int i = size_of_vector; i < new_size; ++i) {
        elements[i]=0;      //初始化为0
    }
    size_of_vector=new_size;        //刷新容器大小数据
}
void VECTOR::push_back(double data)     //放入新元素
{
    static const int minimum_interval=8;
    if (size_of_free_space==0)      //暂未放入任何元素
    {
        reverse(minimum_interval);
    }
    if (size_of_vector==size_of_free_space)     //已经放满了空闲空间
    {
        reverse(size_of_vector*2);      //获取当前大小两倍的空间以备用
    }
    elements[size_of_vector++]=data;        //存入数据
}
VECTOR::~VECTOR()       //析构函数
{
    delete[] elements;
}
int main(){
    VECTOR v;
    v.push_back(5);
    v.resize(2);
    v.push_back(6);
    VECTOR v1=v;
    v1.reverse(5);
    cout<<v1.size()<<endl<<v1[0]<<endl<<v1[1]<<endl<<v1[2];
}