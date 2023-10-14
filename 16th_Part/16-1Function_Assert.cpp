//
// Created by Zhou on 2023/3/14.
//
#include "../Head/std_lib_facilities.h"
class larger_than{
private:
    int data;
public:
    larger_than(int cmp_data):data{cmp_data}{}      //保存参数
    bool operator()(int x){return x>data;}      //比较
};
template<typename T>class Fct{      //函数对象
    T data;     //状态
public:
    Fct(const T&this_data):data{this_data} {}        //建立初始状态
    inline T operator()(T&this_data)const{         //函数调用
        return this_data>data;
    }
    inline const T&state()const{return data;}      //暴露状态
    inline void reset(const T&new_data){data=new_data;}        //重置状态
};
int main(){
    vector<int>v={0,1,2,3,4,5,6,7,8,9};
    auto p= find_if(v.begin(), v.end(), Fct(3));
    if (p!=v.end())cout<<*p<<"larger_than!\n";
    int x;
    auto q= find_if(v.begin(), v.end(), [&](int data){return data>x;});
    if (p!=v.end())cout<<*p<<"larger_than!\n";
}