//
// Created by Zhou on 2023/2/10.
//
#include"../Head/std_lib_facilities.h"
struct Link
{
    string value;
    Link*previous;
    Link*succeed;
    Link(const string&v,Link*prev= nullptr,Link*succ= nullptr)
    :value{v},previous{prev},succeed{succ}{}
};
int main()
{
    Link *norse_gods=new Link{"Thor"};
    //��Odin��ǰ����ΪThor
    norse_gods=new Link{"Odin", nullptr,norse_gods};
    //��Thor(Ҳ����Odin��ǰ��)�ĺ������Odin
    norse_gods->succeed->previous=norse_gods;
    //��Freia��ǰ����ΪOdin
    norse_gods=new Link{"Freia", nullptr,norse_gods};
    //��Odin(Ҳ����Freia��ǰ��)�ĺ������Freia
    norse_gods->succeed->previous=norse_gods;
    cout<<norse_gods->value<<endl
    <<norse_gods->succeed->value<<endl
    <<norse_gods->succeed->succeed->value<<endl;
}