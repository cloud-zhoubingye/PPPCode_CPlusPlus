//
// Created by Zhou on 03/05/2023.
//
#include "../Head/Matrix.h"
#include "../Head/MatrixIO.h"
#include "../Head/std_lib_facilities.h"
using namespace std;
int main(){
    using namespace Numeric_lib;
    int a[][2]={{1,2},{3,4}};
    Matrix<int,2>m0(2,2);
    m0=1;
    Matrix<int,2> m1(a);
    Matrix<int,2>m2(2,2);
    //行交换
    cout<<"Raw_Matrix:\n"<<m1<<endl;
    m1.swap_rows(0,1);
    cout<<"Swap_Rows:\n"<<m1<<endl;
    m1.swap_columns(0,1);
    cout<<"Swap_Columns:\n"<<m1<<endl;
    //乘法
    cout<<"Multiply:\n"<<m1*m0;
    //输入输出
    cin>>m2;
    cout<<"m2:\n"<<m2;
}