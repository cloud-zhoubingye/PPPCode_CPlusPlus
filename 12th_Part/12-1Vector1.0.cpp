//
// Created by Zhou on 2023/2/9.
//
//VECTOR1.0
//仅含最基本设置值，取得值操作
#include "../Head/std_lib_facilities.h"
class  VECTOR
{
private:
    int size_of_vector;
    double* elements;
public:
    VECTOR(int length):size_of_vector{length},elements{new double[length]}{}
    ~VECTOR(){delete[] elements;}
    int size()const {return size_of_vector;}
    double get(int n)const{return elements[n];}
    void set(int n,double value){elements[n]=value;}
};
int main()
{
    VECTOR v(5);
    for (int i = 0; i < v.size(); ++i) {
        v.set(i,(i+1.01)*1.23456);
        cout<<"V["<<i<<"]=="<<v.get(i)<<endl;
    }


}