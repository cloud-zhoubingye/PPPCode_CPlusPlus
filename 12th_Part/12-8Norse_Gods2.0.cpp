//
// Created by Zhou on 2023/2/17
//
#include "../Head/std_lib_facilities.h"
class God{
public:
    string Name;
    string Myth_System;
    string Mount;
    string Weapon;
    God* Next;
    God(string name,string myth_system,string mount,string weapon,God*next= nullptr)
        :Name{name},Myth_System{myth_system},Mount{mount},Weapon{weapon},Next{next}{}
    God* add(God*p);
};
God* God::add(God *p) {
    p->Next=this->Next;
    this->Next=p;
    return p;
}
God* find(God*head,God*p){
    God*q=head->Next;
    while(q){
        if (q==p)
            return q;
        else
            q=q->Next;
    }
    return nullptr;
}
void print_all(God*p){
    while(p){
        cout<<p->Name<<"\t"
        <<p->Mount<<'\t'
        <<p->Myth_System<<'\t'
        <<p->Weapon<<endl;
        p=p->Next;
    }
}
int main(){
    God*p=new God{"Zeus","Greek","Unknown","Lighting"};
    p->add(new God{"Odin","Norse","Eight_legged flying horse called Sleipner","Unknown"});
    print_all(p);
}