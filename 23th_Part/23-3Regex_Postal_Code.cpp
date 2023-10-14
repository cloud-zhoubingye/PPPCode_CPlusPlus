//
// Created by Zhou on 01/05/2023.
//
#include "regex"
#include "iostream"
#include "string"
#include "fstream"
using namespace std;
int main(){
    ifstream in {"../My_Test_txt/23-3Postal_Message.txt"};
    if (!in) cerr<<"no file\n";

    regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"};     //邮政编码格式
    int line_cnt=0;
    for (string line; getline(in,line);){
        ++line_cnt;
        smatch matches;
        if (regex_search(line, matches, pat)){
            cout<<line_cnt<<": "<<matches[0]<<'\n';
            if (matches.size()>1&&matches[1].matched)
                cout<<"\t :"<<matches[1]<<'\n';
        }
    }
}