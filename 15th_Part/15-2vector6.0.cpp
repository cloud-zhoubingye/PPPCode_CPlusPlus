//
// Created by Zhou on 2023/3/10.
//
/*
 * VECTOR6.0
 *
 * 使用我自定义的vector
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
 * 十三，使用allocator类进行未初始化内存管理，将内存分配与初始化分离
 * 十四，使用迭代器进行索引
 * 十五，提供insert()和erase()操作，便于灵活处理少量数据
 * 十六，拥有析构函数，避免内存泄漏
 */
/*
 * 问题：
 * insert函数传入参数：(size_type index, const T&variable)
 * 但是报错传入参数类型错误
 * 报错信息为：In template: cannot initialize return object of type 'iterator' (aka 'double *') with an lvalue of type 'double'
 * 详细信息：
 * error occurred here
 * in instantiation of member function 'vector<double>::end' requested here
 * in instantiation of member function 'vector<double>::insert' requested here
 */
#include "vector6.0.h"
int main(){
    vector<double>v={1.1,2.2,3.3,4.4,5.5};
    v.reverse(7);
    v.push_back(6.6);
    v.push_back(7.7);
    v.insert(2,2.99);       //报错In template: cannot initialize return object of type 'iterator' (aka 'double *') with an lvalue of type 'double'
    v.erase(3);     //报错In template: cannot take the address of an rvalue of type 'const_iterator' (aka 'const double *'）
    cout<<v.find(6.6)<<endl;
    cout<<v;
}