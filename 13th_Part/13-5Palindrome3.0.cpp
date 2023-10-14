//
// Created by Zhou on 2023/2/25.
//
//版本3.0
//使用数组类型，但可以允许无穷多个字符
#include "../Head/std_lib_facilities.h"
bool is_palindrome(const char s[],int n);
bool read_word(istream&is,char*buffer);
int main(){
    constexpr int max=6;
    for(char s[max]; read_word(cin,s);){
        cout<<"Your string"<<" is ";
        if (!is_palindrome(s,strlen(s)))
            cout<<"not ";
        cout<<"a palindrome\n";
    }
}
bool is_palindrome(const char s[],int n){
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
bool read_word(istream&is,char*buffer){
    constexpr int max=6;
    is.width(max);
    char *p=new char[max];
    int cnt=0;
    while(is>>p){
        cnt++;
        char* temp=new char[strlen(buffer)+max];
        for(int i=0;buffer[i];++i){
            temp[i]=buffer[i];
        }
        for(int i=0;p[i];++i){
            temp[strlen(buffer)+i]=p[i];
        }
        buffer=temp;
        is.width(max);
    }
    if(cnt==0)return false;
    return true;
}