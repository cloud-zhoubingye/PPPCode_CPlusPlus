//
// Created by Zhou on 2023/2/1.
//
#include "Punctuate_Stream.h"
using namespace std;
int main()
{
    string s;
    getline(cin,s);
    for(char& ch:s)
    {
        switch (ch) {
            case ',':
            case '?':
            case '!':
            case '.':
            case ';':
                ch=' ';
        }
    }
    stringstream ss {s};
    stringstream ss1;
    for (string s;ss>>s;) {
        cout<<"TOKEN: "<<s<<endl;
        ss1<<s;
    }
    if (ss.eof())
    {
        ss.clear();
    }
    for(char ch;ss1.get(ch);)
    {
        if (isdigit(ch))
        {
            cout<<"DIGIT: "<<ch<<endl;
        }
        else if (isalpha(ch))
        {
            cout<<"ALPHA: "<<ch<<endl;
        }
        else if (isspace(ch))
        {
            cout<<"SPACE"<<ch<<endl;
        }
        else {
            cerr<<"ELSE: "<<ch<<endl;
        }
    }
}