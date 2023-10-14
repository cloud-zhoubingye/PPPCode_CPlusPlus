//
// Created by Zhou on 2023/3/23.
//
#include "map"
#include "iostream"
#include "string"
int main(){
    std::map<std::string,int>words;
    for (std::string s; std::cin>>s;){++words[s];}
    for (const auto &p : words){std::cout<<p.first<<" "<<p.second<<std::endl;}
}