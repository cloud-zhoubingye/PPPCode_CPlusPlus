//
// Created by Zhou on 03/05/2023.
//
#include "../Head/Matrix.h"
#include "../Head/std_lib_facilities.h"
using namespace std;
double scale(double d,double s){return d*s;}
int main(){
    using namespace Numeric_lib;
    int a[]={2,2,2,2,2,2,2,2};
    Matrix<int,1>v(a);
    Matrix<int>v1(8);
    //广播函数
    v1=apply(scale,v,2);
    cout<<v1[0]<<endl;
    //融合乘-加运算
    v1= scale_and_add(v1,2,v);
    cout<<v1[0]<<endl;
    //点积
    int r= dot_product(v,v1);
    cout<<r<<endl;
}