//
// Created by Zhou on 2023/3/10.
//

#ifndef C__PRINCIPLES_AND_PRACTISE_VECTOR6_0_H
#define C__PRINCIPLES_AND_PRACTISE_VECTOR6_0_H
#include <stdexcept>        //提供out_of_range标准异常
#include <memory>       //提供allocator分配器
#include <iostream>         //重载输入输出流
using namespace std;
struct out_of_vector_range: out_of_range{     //增强的VECTOR越界报告
    int index;
    explicit out_of_vector_range(int i): out_of_range("RANGE_ERROR: out_of_vector_range !"), index{i}{}
};
template<typename T,typename A=allocator<T>>
class vector{       //A提供可选的默认参数
private:
    int size_of_vector;      //大小
    int size_of_free_space;      //空闲空间
    T* elements;     //指向元素的指针
    A alloc;        //分配器
public:
    using size_type=unsigned long;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    iterator begin();       //返回指向头部位置的迭代器
    const_iterator begin()const;
    iterator end();         //返回指向尾元素的下一个位置的迭代器
    const_iterator end()const;
    value_type& front();       //返回首元素的引用
    value_type& back();       //返回尾元素的引用
    T& at(int n);        //带范围检查的读写元素
    const T& at(int n)const;        //带范围检查的读写元素
    T& operator[](int n);      //不带范围检查的读写元素
    const T& operator[](int n)const;      //不带范围检查的读取const VECTOR中的元素
    size_type size()const{return size_of_vector;}     //返回已使用空间大小
    size_type capacity()const{return size_of_free_space;}        //返回预留空间大小
    vector(): size_of_vector{0}, size_of_free_space{0}, elements{nullptr}{}        //默认构造函数
    explicit vector(int length);       //构造函数
    vector(initializer_list<T>list);       //初始化器列表构造函数
    vector(const vector&arg);    //拷贝构造函数
    vector& operator=(const vector&arg);        //拷贝赋值函数
    vector(vector&&arg);        //移动构造函数
    vector& operator=(vector&&arg);      //移动赋值
    void reverse(int new_allocate);     //增加预留空间
    void resize(int new_size,T define_initial=T());      //重设大小
    void push_back(const T& data);        //放入新元素
    void pop_back();        //弹出最后一个元素
    iterator insert(size_type index, const T&val);        //插入(到该元素前)
    iterator erase(size_type index);         //删除
    iterator find(const value_type& variable);      //查找
    void destroy();     //销毁
    ~vector();       //析构函数
};
template<typename T,typename A>vector<T,A>::iterator  vector<T,A>::begin() {
    return elements;
}
template<typename T,typename A>vector<T,A>::const_iterator vector<T,A>::begin()const {
    return elements;
}
template<typename T,typename A>vector<T,A>::iterator vector<T,A>::end() {
    return elements[size()];
}
template<typename T,typename A>vector<T,A>::const_iterator vector<T,A>::end()const {
    return elements[size()];
}
template<typename T,typename A>vector<T,A>::value_type& vector<T,A>::front(){
    return elements[0];
}
template<typename T,typename A>vector<T,A>::value_type& vector<T,A>::back(){
    return elements[size()-1];
}
template<typename T,typename A>T& vector<T,A>::at(int n) {
    if (n<0||n>=size()) throw out_of_vector_range{n};
    return elements[n];
}
template<typename T,typename A>const T& vector<T,A>::at(int n) const {
    if (n<0||n>=size()) throw out_of_vector_range{n};
    return elements[n];
}
template<typename T,typename A>T& vector<T,A>::operator[](int n) {
    return elements[n];
}
template<typename T,typename A>const T& vector<T,A>::operator[](int n)const {
    return elements[n];
}
template<typename T,typename A>vector<T,A>::vector(int length)
        :size_of_vector{length},size_of_free_space{length},elements{new double[length]} {
    for (int i = 0; i < length; ++i) {
        elements[i] = 0;
    }
}
template<typename T,typename A>vector<T,A>::vector(initializer_list<T>list) {
    size_of_vector = size_of_free_space = list.size();
    copy(list.begin(), list.end(), elements);
}
template<typename T,typename A>vector<T,A>::vector(const vector&arg) {
    size_of_free_space=size_of_vector=arg.size();
    elements=new double[arg.size()];
    copy(arg.elements,arg.elements+arg.size()-1,elements);
}
template<typename T,typename A>vector<T,A>& vector<T,A>::operator=(const vector&arg) {
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
template<typename T,typename A>vector<T,A>::vector(vector &&arg) {
    size_of_vector=size_of_free_space=arg.size();
    elements=arg.elements;
    arg.elements= nullptr;
    arg.size_of_vector=arg.size_of_free_space=0;
}
template<typename T,typename A>vector<T,A>& vector<T,A>::operator=(vector&&arg) {
    delete[] elements;
    elements=arg.elements;
    size_of_vector=size_of_free_space=arg.size();
    arg.elements= nullptr;
    arg.size_of_vector=arg.size_of_free_space=0;
    return *this;
}
template<typename T,typename A>void vector<T,A>::reverse(int new_allocate) {
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
template<typename T,typename A>void vector<T,A>::resize(int new_size, T define_initial) {
    reverse(new_size);
    for (int i = size(); i < new_size; ++i) {       //如果变得更大
        alloc.construct(&elements[i], define_initial);       //构造并赋初值
    }
    for (int i = new_size; i < size(); ++i) {       //如果变得更小
        alloc.destroy(&elements[i]);        //销毁
    }
    size_of_vector=new_size;
}
template<typename T,typename A>void vector<T,A>::push_back(const T& data) {
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
template<typename T,typename A>void vector<T,A>::pop_back() {
    if (size()==0) return;
    --size_of_vector;
    alloc.destroy(elements[size()-1]);
}
template<typename T,typename A>vector<T,A>::iterator vector<T,A>::insert(size_type index, const T&variable) {
    if (size()==capacity()){
        constexpr int Minimum_Interval=8;
        reverse(size()==0?Minimum_Interval:2*size());       //扩展内存时原迭代器会失效，仍指向原内存
    }
    //将最后一个元素的值构造到未初始化的下一个位置(迭代器不能指向序列之外)
    alloc.construct(elements+size(),back());
    ++size_of_vector;
    iterator new_p= begin() + index;       //插入后指向该插入元素的新迭代器
    for (auto position=new_p;position!=end()-1;++position){
        *(position+1)=*position;        //拷贝其余元素(含p位置上原本有的元素)
    }
    *(new_p)=variable;        //最后插入待插入的变量值
    return new_p;
}
template<typename T,typename A>vector<T,A>::iterator vector<T,A>::erase(size_type index) {
    auto p=&elements[index];
    if (p==end()) return p;
    for (auto position = p+1; position!=end() ; ++position) {
        *(position-1)=*position;        //把元素拷贝至左边一个位置
    }
    alloc.destroy(&(end()-1));      //销毁(已经拷贝移走的)最后一个元素，使总元素-1
    size_of_vector--;       //移除一个后，元素个数-1
    return p;
}
template<typename T,typename A>vector<T,A>::iterator vector<T,A>::find(const value_type &variable) {
    for (iterator p=begin(); p != end(); ++p){
        if (*p==variable) return p;
    }
    return end();
}
template<typename T,typename A>void vector<T,A>::destroy() {
    ~vector<T,A>();
}
template<typename T,typename A>vector<T,A>::~vector() {
    delete[] elements;
}
template<typename T,typename A>ostream& operator<<(ostream &os, const vector<T,A>&v) {
    for (int i = 0; i < v.size(); ++i) {
        os<<"v["<<i<<"]="<<v.at(i)<<'\t';
    }
    return os;
}
template<typename T,typename A>istream& operator>>(istream &is, vector<T,A>&v) {
    for(T v_elem;is>>v_elem;) {
        v.push_back(v_elem);
    }
    is.clear(ios::goodbit);
}
#endif //C__PRINCIPLES_AND_PRACTISE_VECTOR6_0_H