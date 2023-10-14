//
// Created by Zhou on 04/05/2023.
//
#include "../Head/std_lib_facilities.h"
int ran_int(int max){
    std::random_device seed;
    std::default_random_engine ran{seed()};
    std::uniform_int_distribution<> real{0,max};
    return real(ran);
}
void print_star(const int n){
    for (int i = 0; i < n; ++i) {
        cout<<'*';
    }
    cout<<endl;
}
int main(){
    {
        cout<<"---------------------------\n";
        map<int,int> m;
        for (int i = 0; i < 1000; ++i) {
            int num= randint(20);
            ++m[num];
        }
        for (auto p:m) {
            print_star(p.second);
        }
        cout<<"---------------------------\n\n\n\n\n";
    }
    {
        cout<<"---------------------------\n";
        map<int,int> m;
        for (int i = 0; i < 1000; ++i) {
            int num= ran_int(20);
            ++m[num];
        }
        for (auto p:m) {
            print_star(p.second);
        }
        cout<<"---------------------------\n";
    }
    cout<<"Result:\n"<<"default_random_engine is better than uniform_int_distribution\n";
}