//
// Created by Zhou on 2023/2/10.
//
#include "../Head/std_lib_facilities.h"
void increase(int&x)
{
    x++;
}
int main()
{
    const int var=reinterpret_cast<char>(' ');
    cout<<var<<endl;
    int*ptr=const_cast<int*>(&var);
    void* ptr1=ptr;
    int*ptr2=static_cast<int*>(ptr1);
    cout<<ptr2<<'\t'<<*ptr2<<endl;
    increase(*ptr);
    cout<<"var:"<<var<<endl<<"ptr_var:"<<*ptr2<<endl;
}