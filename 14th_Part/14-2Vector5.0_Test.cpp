//
// Created by Zhou on 2023/2/28.
//
#include "vector5.0.h"
int main(){
    VECTOR<int>v;
    v.reverse(5);
    cout<<"Capacity:"<<v.capacity()<<endl;
    v.push_back(1);
    v.resize(11);
    cout<<"Size:"<<v.size()<<endl;
    v.at(1)=2;
    v[2]=3;
    cout<<v<<endl;
    try{
        v.push_back(4);
        v.at(100)=9999;
    }
    catch(out_of_VECTOR_range&e) {
        cout<<e.what()<<'\n'<<"Wrong Visit Place:"<<e.index<<endl;
    }
}
