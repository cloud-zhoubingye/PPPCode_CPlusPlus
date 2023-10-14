//
// Created by Zhou on 2023/2/5.
//
#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
using namespace std;
int main()
{
    vector<string>word;
    string line;
    while(getline(cin,line))
    {
        bool is_skip = false;
        for (char &ch: line)
            if (isalpha(ch))
                ch = tolower(ch);
            else if (ch == '"'&&!is_skip)
                is_skip = true;
            else if (ch == '"'&&is_skip)
                is_skip = false;
            else if (is_skip || ch == '-' || ch == '_' || ch == '\'');
                else
                    ch = ' ';
        istringstream iss;
        iss.str(line);
        string wd;
        while (iss >> wd)
        {
            if (wd=="don't")
                wd="do not";
            else if (wd=="can't")
                wd="can not";
            word.push_back(wd);
        }
        iss.clear();
    }
    for (const string& s: word)
        cout << s << ' ';
    cout<<endl;
}
