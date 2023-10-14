//
// Created by Zhou on 2023/3/20.
//
#include "iostream"
#include "algorithm"
#include "iterator"
using namespace std;
struct No_case{
    bool operator()(const string&a,const string&b) {
        for (int i = 0; i < a.size(); ++i) {
            //b的长度更短，a还未到末尾，但b却已经到末尾
            if (i==b.size()) {
                return false;
            }
            char ch_a= ::tolower(a[i]);
            char ch_b= ::tolower(b[i]);
            //第一个不同的字符处，a更小
            if (ch_a<ch_b) return true;
            //第一个不同的字符处，b更小
            if (ch_a>ch_b) return false;
        }
        //a的长度更短，b还未到末尾，但a却已经到末尾退出了循环
        if (a.size()==b.size()) return true;
        //a,b长度和每个字符都相等
        if (a.size()==b.size()) return false;
    }
};
int main(){
    vector<string>v{istream_iterator<string>{cin},istream_iterator<string>{}};
    sort(v.begin(),v.end(),No_case());
    auto p=equal_range(v.begin(),v.end(),"a");
    copy(p.first,p.second,ostream_iterator<string>{cout,"\n"});
}