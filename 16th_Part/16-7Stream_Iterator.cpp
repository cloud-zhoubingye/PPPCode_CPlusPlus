//
// Created by Zhou on 2023/3/19.
//
#include "iterator"
#include "iostream"
#include "fstream"
#include "set"
#include "algorithm"
using namespace std;
int main(){
    ostream_iterator<string>oo{cout};
    *oo="What's your first_name my dear?\n";    //表示cout<<"..."
    ++oo;       //准备好下一个输入操作
    istream_iterator<string>ii{cin};
    string s=*ii;       //表示读取到s中
    *oo="Hello ";
    ++oo;
    *oo=s;
    ++oo;
    *oo=" !\n";

    //两行实现输入，读取，排序，去重，输出
    set<string>v{istream_iterator<string>{cin},istream_iterator<string>{}};
    copy(v.begin(),v.end(),ostream_iterator<string>{cout,"\n"});
}