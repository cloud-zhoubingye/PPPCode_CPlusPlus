//
// Created by Zhou on 2023/3/16.
//
#include <string>
#include <vector>
#include <algorithm>
struct Stu{
    std::string name;
    double score;
};
struct cmp_by_name{
    bool operator()(const Stu&s1,const Stu&s2)const{return s1.name<s2.name;}
};
struct cmp_by_score{
    bool operator()(const Stu&s1,const Stu&s2)const{return s1.score<s2.score;}
};
int main(int argc,char**argv) {
    std::vector<Stu> v = {Stu{"A", 100}, Stu{"B", 99}, Stu{"C", 59}};
    std::sort(v.begin(), v.end(), cmp_by_name());       //报错'cmp_by_name' does not refer to a value
    sort(v.begin(), v.end(), cmp_by_score());       //报错'cmp_by_score' does not refer to a value
    sort(v.begin(), v.end(), [](const Stu &s1, const Stu &s2) { return s1.name < s2.name; }); //正确
    sort(v.begin(), v.end(), [](const Stu &s1, const Stu &s2) { return s1.name < s2.name; }); //正确
}