//
// Created by Zhou on 2023/2/17.
//
#include "../Head/std_lib_facilities.h"
int main()
{
    int* storage_1=new int{1};
    int* storage_2=new int{1};
    cout<<"FREE STORY:"<<endl;
    cout<<"int 1: "<<storage_1<<endl
    <<"int 2: "<<storage_2<<endl;
    int i=0,k=0;
    int*storage_3=&i;
    int *storage_4=&k;
    cout<<"STACK:"<<endl;
    cout<<"int 1: "<<storage_3<<endl
        <<"int 2: "<<storage_4<<endl;
}