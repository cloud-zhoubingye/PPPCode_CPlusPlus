//
// Created by Zhou on 2023/2/16.
//
#include "../Head/std_lib_facilities.h"
int main()
{
    try{
        for (unsigned long long i=1;;i++) {
            int*p=new int[1000000];
            cout<<"已分配 "<<(double(1000000)/1073741824)*sizeof(int)*i<<" GB内存"<<endl;
        }
    }
    catch(bad_alloc&e){
        cerr<<"Over!: "<<e.what()<<endl;
    }
}