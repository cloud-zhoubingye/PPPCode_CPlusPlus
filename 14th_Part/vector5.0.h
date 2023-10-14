//
// Created by Zhou Bing Ye on 2023/3/4.
//
/*
 * VECTOR5.0
 *
 * 支持十四大功能特性
 * 一，拥有默认构造函数，解决漏掉初始化的麻烦
 * 二，拥有接受一个参数或参数列表的构造函数
 * 三，拥有拷贝构造函数和拷贝赋值操作，实现深拷贝，避免内存泄漏和重复释放
 * 四，对于自赋值以及空间足够的赋值，有效避免了不必要的内存分配与释放
 * 五，拥有移动构造函数和移动赋值操作，将元素的所有权从函数移出，避免智能指针的复杂性
 * 六，单参数构造函数均为更安全的显式限定，避免隐式类型转换
 * 七，支持[]取下标操作进行值的访问与修改，支持[]对const VECTOR进行值的访问
 * 八，提供at(int n)操作，实现带对VECTOR和const VECTOR范围检查的元素访问，提供强保证
 * 九，提供可选的读写值范围检查，兼顾效率和安全
 * 十，允许用户知晓已用空间和预留空间的大小，并改变已用空间或增加预留空间
 * 十一，支持push_back操作，同时以加倍式内存扩张战略减少反复复制的过程
 * 十二，支持多种类型，并且支持自定义初始化值(也允许不单独进行初始化)
 * 十三，使用allocator类和智能指针unique_ptr进行未初始化内存管理
 * 十四，拥有析构函数，避免内存泄漏
 */

#ifndef C__PRINCIPLES_AND_PRACTISE_VECTOR_H
#define C__PRINCIPLES_AND_PRACTISE_VECTOR_H

#include "../Head/std_lib_facilities.h"
struct out_of_VECTOR_range:out_of_range{     //增强的VECTOR越界报告
    int index;
    explicit out_of_VECTOR_range(int i): out_of_range("RANGE_ERROR: out_of_VECTOR_range !"),index{i}{}
};
template<typename T,typename A=allocator<T>>
        class VECTOR{       //A提供可选的默认参数
private:
    int size_of_vector;      //大小
    int size_of_free_space;      //空闲空间
    T* elements;     //指向元素的指针
public:
    A alloc;        //分配器
    T& at(int n);        //带范围检查的读写元素
    const T& at(int n)const;        //带范围检查的读写元素
    T& operator[](int n);      //不带范围检查的读写元素
    const T& operator[](int n)const;      //不带范围检查的读取const VECTOR中的元素
    int size()const{return size_of_vector;}     //返回已使用空间大小
    int capacity()const{return size_of_free_space;}        //返回预留空间大小
    VECTOR():size_of_vector{0},size_of_free_space{0},elements{nullptr}{}        //默认构造函数
    explicit VECTOR(int length);       //构造函数
    VECTOR(initializer_list<T>list);       //初始化器列表构造函数
    VECTOR(const VECTOR&arg);    //拷贝构造函数
    VECTOR& operator=(const VECTOR&arg);        //拷贝赋值函数
    VECTOR(VECTOR&&arg);        //移动构造函数
    VECTOR& operator=(VECTOR&&arg);      //移动赋值
    void reverse(int new_allocate);     //增加预留空间
    void resize(int new_size,T define_initial=T());      //重设大小
    void push_back(const T& data);        //放入新元素
    ~VECTOR();       //析构函数
};

template<typename T,typename A>T& VECTOR<T,A>::at(int n) {
    if (n<0||n>=size()) throw out_of_VECTOR_range{n};
    return elements[n];
}
template<typename T,typename A>const T& VECTOR<T,A>::at(int n) const {
    if (n<0||n>=size()) throw out_of_VECTOR_range{n};
    return elements[n];
}
template<typename T,typename A>T& VECTOR<T,A>::operator[](int n) {
    return elements[n];
}
template<typename T,typename A>const T& VECTOR<T,A>::operator[](int n)const {
    return elements[n];
}
template<typename T,typename A>VECTOR<T,A>::VECTOR(int length)
        :size_of_vector{length},size_of_free_space{length},elements{new double[length]} {
    for (int i = 0; i < length; ++i) {
        elements[i] = 0;
    }
}
template<typename T,typename A>VECTOR<T,A>::VECTOR(initializer_list<T>list) {
    size_of_vector = size_of_free_space = list.size();
    copy(list.begin(), list.end(), elements);
}
template<typename T,typename A>VECTOR<T,A>::VECTOR(const VECTOR&arg) {
    size_of_free_space=size_of_vector=arg.size();
    elements=new double[arg.size()];
    copy(arg.elements,arg.elements+arg.size()-1,elements);
}
template<typename T,typename A>VECTOR<T,A>& VECTOR<T,A>::operator=(const VECTOR&arg) {
    if (&arg==this) return *this;
    if(arg.size()<=capacity()){
        copy(arg.elements,arg.elements+arg.size()-1,elements);
        size_of_vector=arg.size();
        return *this;
    }
    delete[] elements;
    elements=new double[arg.size()];
    size_of_vector=size_of_free_space=arg.size();
    copy(arg.elements,arg.elements+arg.size()-1,elements);
    return *this;
}
template<typename T,typename A>VECTOR<T,A>::VECTOR(VECTOR &&arg) {
    size_of_vector=size_of_free_space=arg.size();
    elements=arg.elements;
    arg.elements= nullptr;
    arg.size_of_vector=arg.size_of_free_space=0;
}
template<typename T,typename A>VECTOR<T,A>& VECTOR<T,A>::operator=(VECTOR&&arg) {
    delete[] elements;
    elements=arg.elements;
    size_of_vector=size_of_free_space=arg.size();
    arg.elements= nullptr;
    arg.size_of_vector=arg.size_of_free_space=0;
    return *this;
}
template<typename T,typename A>void VECTOR<T,A>::reverse(int new_allocate) {
    if (capacity()>=new_allocate) return;
    size_of_free_space=new_allocate;
    T *p=alloc.allocate(new_allocate);      //分配新空间
    for (int i = 0; i < size(); ++i) {
        alloc.construct(&p[i],elements[i]);     //拷贝
    }
    for (int i = 0; i < size(); ++i) {
        alloc.destroy(&elements[i]);        //销毁
    }
    alloc.deallocate(elements,capacity());        //释放旧空间
    elements=p;
}
template<typename T,typename A>void VECTOR<T,A>::resize(int new_size, T define_initial) {
    reverse(new_size);
    for (int i = size(); i < new_size; ++i) {       //如果变得更大
        alloc.construct(&elements[i], define_initial);       //构造并赋初值
    }
    for (int i = new_size; i < size(); ++i) {       //如果变得更小
        alloc.destroy(&elements[i]);        //销毁
    }
    size_of_vector=new_size;
}
template<typename T,typename A>void VECTOR<T,A>::push_back(const T& data) {
    if (size()==0&&capacity()==0) {
        constexpr int Minimum_Interval=8;
        reverse(Minimum_Interval);
    }
    if (size()==capacity()) {
        reverse(size()*2);
    }
    alloc.construct(&elements[size()],data);
    ++size_of_vector;
}
template<typename T,typename A>VECTOR<T,A>::~VECTOR() {
    delete[] elements;
}
template<typename T,typename A>ostream& operator<<(ostream &os,VECTOR<T,A>&v) {
    for (int i = 0; i < v.size(); ++i) {
        os<<"v["<<i<<"]="<<v.at(i)<<'\t';
    }
    return os;
}
#endif //C__PRINCIPLES_AND_PRACTISE_VECTOR_H
