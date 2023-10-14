//
// Created by Zhou on 2023/3/23.
//
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
template<typename Iterator, typename T>
Iterator Binary_Search(Iterator first, Iterator last, const T target) {
    //不支持map，list，set，unordered_map等，他们存储不是连续的
    if (first==last)return last;
    Iterator middle=first+(last-first)/2;
    if (*middle==target) return middle;
    if (*middle>target) return Binary_Search(first,middle,target);
    if (*middle<target) return Binary_Search(middle,last,target);
}
int main(){
    vector<int>v={1,65,54,65,76,34,56,6,835,8,5,9,32,78,4,76,34,0,64,67,3,75,34,64,-5};
    vector<string>l={"zz","ss","fga","aaa","bbb","qaq","aza"};
    sort(v.begin(),v.end());
    sort(l.begin(),l.end());
    auto p_v= Binary_Search(v.begin(),v.end(),56);
    auto p_l= Binary_Search(l.begin(),l.end(),"qaq");
    cout<<*p_v<<endl<<*p_l<<endl;
}