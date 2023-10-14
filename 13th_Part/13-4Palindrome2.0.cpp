//
// Created by Zhou on 2023/2/25.
//
#include "../Head/std_lib_facilities.h"
using namespace std;
bool is_palindrome(const char s[],int n){
    //版本2.0
    //使用数组类型
    int first=0;
    int last=n-1;
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
istream&read_word(istream&is,char*buffer,int max){
    is.width(max);
    is>>buffer;
    return is;
}
int main(){
    constexpr int max=128;
    for(char s[max]; read_word(cin,s,max);){
        cout<<s<<" is ";
        if (!is_palindrome(s,strlen(s)))
            cout<<"not ";
        cout<<"a palindrome\n";
    }
}