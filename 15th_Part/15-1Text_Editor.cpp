//
// Created by Zhou on 2023/3/9.
//
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
/*
 * 文本搜索器
 * 文本存储结构：vector<list<Line>::iterator>    ----》  list<Line>    ----》  vector<char>
 *
 * 原理：
 * 将一行的内容存入vector<char>，并将文本用list<vector<char>来按行存储，
 * 以此减少插入，删除时的复制损耗。为此，定义了一个迭代器，
 * 该迭代器跨越行的限制，当指向某行的最后一个char时，会移动到下一行的第一个char
 */
/*
 * 问题：find()函数调用时，报错In template: no matching function for call to '__iterator_category'
 * 具体信息：
 * error occurred here
 * in instantiation of function template specialization 'std::__find_if<Text_iterator, __gnu_cxx::__ops::_Iter_equals_val<const char[4]>>' requested here
 * in instantiation of function template specialization 'std::find<Text_iterator, char[4]>' requested here
 * candidate template ignored: substitution failure [with _Iter = Text_iterator]: no type named 'iterator_category' in 'std::iterator_traits<Text_iterator>'
 */
using Line=std::vector<char>;        //一行用存储字符的向量表示
class Text_iterator {
private:
    //自定义迭代器，在行内跟踪行和字符位置
    std::list<Line>::iterator line_list_iter;
    Line::iterator char_vector_iter;
public:
    //迭代器从行this_line中位置this_char处的字符开始
    Text_iterator(std::list<Line>::iterator this_line,Line::iterator this_char)
            : line_list_iter{this_line}, char_vector_iter{this_char}{}
    char& operator*(){return *char_vector_iter;}
    Text_iterator& operator++();        //自定义iterator的根本目的，解决行与行之间的问题
    bool operator==(const Text_iterator&another)const;
    bool operator!=(const Text_iterator&another)const;
};
struct Document{        //一个文档用行的链表表示
    std::list<Line>line;
    Document(){line.push_back(Line{});}
    friend std::istream& operator>>(std::istream&is,Document&document);
    friend std::ostream& operator<<(std::ostream&os,Document&document);
    Text_iterator begin();
    Text_iterator end();
};

template<typename Iter>void move_to_line(Iter&p,int pace){
    if (pace>0){
        while(pace>0){
            ++p;
            --pace;
        }
    }
    if(pace<0){
        while(pace<0){
            --p;
            ++pace;
        }
    }
}
void erase_line(Document&document,int n){
    if (n<0||n>=document.line.size()-1) return;
    auto p=document.line.begin();
    move_to_line(p,n);
    document.line.erase(p);
}
Text_iterator& Text_iterator::operator++() {
    ++char_vector_iter;
    if (char_vector_iter == (*line_list_iter).end()){
        ++line_list_iter;
        char_vector_iter=line_list_iter->begin();
    }
    return *this;
}
bool Text_iterator::operator==(const Text_iterator &another) const {
    return line_list_iter==another.line_list_iter && char_vector_iter == another.char_vector_iter;
}
bool Text_iterator::operator!=(const Text_iterator &another) const {
    return *this==another;
}
std::istream& operator>>(std::istream&is,Document&document) {
    for (char ch;is.get(ch);) {
        document.line.back().push_back(ch);     //向尾行中添加字符
        if (ch=='\n') {
            document.line.push_back(Line{});        //添加一行，使得下一行在读入时直接写入该空行
        }
    }
    if (document.line.size()!=0) {
        document.line.push_back(Line{});        //添加最后的空行
    }
    return is;
}
std::ostream& operator<<(std::ostream&os,Document&document){
    for (auto i:document.line) {
        for (auto j:i) {
            os<<j;
        }
    }
    return os;
}
Text_iterator Document::begin() {
    return Text_iterator{line.begin(),line.begin()->begin()};
}
Text_iterator Document::end() {
    auto last=line.end();
    --last;     //最后一个是读入时放入的空行
    return Text_iterator{last,last->end()};
}
Text_iterator find_first_char(Text_iterator first,Text_iterator last,char ch){
    while((*first)!=ch){
        ++first;
        if (first==last){
            return last;
        }
    }
    return first;
}
bool match(Text_iterator first, const std::string&s){
    for (char ch:s) {
        if (*first==ch) ++first;
        else return false;
    }
    return true;
}
Text_iterator replace_char(Text_iterator first,const std::string&txt){
    auto first_place=first;
    for (char ch:txt) {
        *first=ch;
        ++first;
    }
    return first_place;
}
//孔诗磊 刘世光
Text_iterator replace(Text_iterator first,Text_iterator last,const std::string&to_be_place,const std::string&txt){
    auto p=std::find(first,last,to_be_place);
    if (p==last)return p;       //没找到匹配字符串
    return replace_char(p,txt);
}
Text_iterator replace_char_return_last(Text_iterator first,const std::string&txt){
    for (char ch:txt) {
        *first=ch;
        ++first;
    }
    return first;
}
unsigned int count(Text_iterator first,Text_iterator last,const std::string&to_be_count){
    //允许覆盖式
    unsigned int cnt=0;
    for (auto p=first;p!=last;++p) {
        if (*p==to_be_count[0]){
            if (match(p,to_be_count)){
                ++cnt;
            }
        }
    }
    return cnt;
}
int main(){
    Document d;
    std::cin>>d;
    std::cout<<d;
    erase_line(d,1);
    std::cout<<d;
    auto p=(std::find(d.begin(),d.end(),"aaa"));
    if (p==d.end())std::cout<<"NOT FOUND\n";
    else std::cout<<"FIND IT\n";
    replace(d.begin(),d.end(),"aaa","Find_it!");
    std::cout<<d;
    std::cout<<count(d.begin(),d.end(),"i");
}