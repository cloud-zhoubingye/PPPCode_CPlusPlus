//
// Created by Zhou on 2023/3/20.
//
#include "iostream"
#include "algorithm"
#include "iterator"
#include "vector"
using namespace std;
template<typename T>class Cmp{
private:
    T standard;
public:
    Cmp(const T&init_s): standard{init_s}{}
    bool operator()(const T& s)const{
        if (s>=standard) return true;
        else return false;
    }
};
template<typename Iterator, typename Compare>
unsigned long long count_if_above(Iterator first, Iterator last, const Compare&cmp){
    unsigned long long counter=0;
    while (first++!=last){
        if (cmp(*first)) ++counter;
    }
    return counter;
}
int main(){
    vector<int>v{istream_iterator<int>{cin},istream_iterator<int>{}};
    cout<<count_if_above(v.begin(),v.end(),Cmp<int>{5});
}

