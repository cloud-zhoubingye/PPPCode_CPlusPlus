//
// Created by Zhou on 03/05/2023.
//
#include "../Head/std_lib_facilities.h"
int main(){
    float x=1.0/333;
    float sum=0;
    for (int i = 0; i < 333; ++i)
        sum += x;
    cout<<setprecision(15)<<"Standard Value: \t"
    <<fixed<<1.0<<"\nActually Value: \t"<<sum<<endl;
}