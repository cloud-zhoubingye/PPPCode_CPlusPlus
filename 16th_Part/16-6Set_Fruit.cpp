//
// Created by Zhou on 2023/3/19.
//
#include "vector"
#include "iostream"
#include "set"
#include "algorithm"
using namespace std;
struct Fruit{
    string name;
    int amount;
    double price;
};
struct Fruit_Order{
    bool operator()(const Fruit&a,const Fruit&b)const
    {return a.name<b.name;}
};
struct copy_limit{
    int amount;
    explicit copy_limit(int amt):amount{amt}{}
    bool operator()(const Fruit&f){return f.amount>amount;}
};
int main(){
    set<Fruit,Fruit_Order>my_fruit={
            Fruit{"A",10,5.5},
            Fruit{"B",15,6.8},
            Fruit{"C",25,8.8}
    };
    my_fruit.insert(Fruit{"D",18,9.9});
    vector<Fruit>v(2);
    copy_if(my_fruit.begin(),my_fruit.end(),v.begin(),copy_limit(16));
    for (auto p=my_fruit.begin();p!=my_fruit.end();p++){
        cout<<p->name<<"\t\t"<<p->price<<"\t\t"<<p->amount<<endl;
    }
    cout<<"------------------------------------"<<endl;
    for (auto p=v.begin();p!=v.end();p++){
        cout<<p->name<<"\t\t"<<p->price<<"\t\t"<<p->amount<<endl;
    }
}