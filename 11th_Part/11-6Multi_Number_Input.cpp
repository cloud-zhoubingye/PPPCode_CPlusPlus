//
// Created by Zhou on 2023/2/5.
//
#include "std_lib_facilities.h"
constexpr int DEC{0};
constexpr int OCT{1};
constexpr int HEX{2};
int main()
{
    while(true)
    {
        unsigned long long num;
        char ch;
        cin>>ch;
        if (ch=='0')
        {
            char is_hex;
            cin>>is_hex;
            if (!cin)
            {
                //是十进制0
                goto here;
            }
            if (is_hex=='x'||is_hex=='X')
            {
                //是十六进制
                cin>>hex>>num;
                cout<<showbase<<hex<<num<<'\t'
                    <<" Hexadecimal converts to "<<dec<<num<<'\t'
                    <<" Decimal"<<endl;
            }
            else {
                //是八进制
                cin>>oct>>num;
                cout<<showbase<<oct<<num<<'\t'
                    <<" Octal converts to "<<dec<<num<<'\t'
                    <<" Decimal"<<endl;
            }
        }
        else{
            here:
            cin.putback(ch);
            cin>>dec>>num;
            if (!cin)return 0;
            cout<<showbase<<dec<<num<<'\t'
                <<" Decimal converts to "<<dec<<num<<'\t'
                <<" Decimal"<<endl;
        }
    }
}