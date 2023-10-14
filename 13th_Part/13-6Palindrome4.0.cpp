//
// Created by Zhou on 2023/2/25.
//
#include "../Head/std_lib_facilities.h"
using namespace std;
bool is_palindrome(const char*first, const char*last){
    //版本4.0
    //使用指针类型
    if(first<last)
        if (*first!=*last) return false;
        else return is_palindrome(++first,--last);
    return true;
}
istream&read_word(istream&is,char*buffer,int max){
    is.width(max);
    is>>buffer;
    return is;
}
int main() {
    constexpr int max = 128;
    for (char s[max]; read_word(cin, s, max);) {
        cout << s << " is ";
        if (!is_palindrome(&s[0],&s[strlen(s)-1]))
            cout << "not ";
        cout << "a palindrome\n";
    }
}