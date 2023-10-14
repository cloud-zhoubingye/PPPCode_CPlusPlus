//
// Created by Zhou on 2023/2/17.
//
#include "../Head/std_lib_facilities.h"
int main()
{
    int*p=new int[4];
    for (int i = 0; i < 5; ++i) {
        int num;
        cin>>num;
        p[i]=num;
    }
    cout<<p[0]<<p[1]<<p[2]<<p[3]<<p[4];
    //不会报错
}