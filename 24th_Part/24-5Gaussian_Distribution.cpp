//
// Created by Zhou on 04/05/2023.
//
#include "random"
#include "functional"
#include "iostream"
using namespace std;
int main(){
    auto gen=bind(normal_distribution<double>{15,4.0},default_random_engine{});
    vector<int>hist(2*15);
    for (int i = 0; i < 500; ++i) {
        ++hist[int(round(gen()))];
    }
    for (int i = 0; i < hist.size(); ++i) {
        cout<<i<<"\t";
        for (int j = 0; j < hist[i]; ++j) {
            cout<<'*';
        }
        cout<<endl;
    }
}