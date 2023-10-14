//
// Created by Zhou on 2023/2/25.
//
#include "../Head/std_lib_facilities.h"
using namespace std;
bool is_palindrome(const string& s){
    //版本1.0
    //使用string类型
    int first=0;
    int last=s.size()-1;
    while(first<last){
        if (s[first]!=s[last]){
            return false;
        }
        else{
            ++first;
            --last;
        }
    }
    return true;
}
int main(){
    for(string s;cin>>s;){
        cout<<s<<" is ";
        if (!is_palindrome(s))
            cout<<"not ";
        cout<<"a palindrome\n";
    }
}