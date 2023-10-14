//
// Created by Zhou on 30/04/2023.
//
#include "string"
#include "vector"
#include "map"
#include "fstream"
#include "iostream"
using namespace std;
using Line_iter=vector<string>::const_iterator;
class Message{
    //一个Message指向一封邮件的首行和尾行
private:
    Line_iter first;
    Line_iter last;
public:
    Message(Line_iter first_line, Line_iter last_line) : first{first_line}, last{last_line}{}
    Line_iter begin() const {return first;}
    Line_iter end() const {return last;}
};
using Message_iter=vector<Message>::const_iterator;
class Mail_file{
    //一个Mail_file保存文件所有行并简化了邮件的访问
public:
    string name;    //文件名
    vector<string>lines;    //保存的行
    vector<Message>messages;    //保存的邮件
    Mail_file(const string&file);   //读取文件保存到lines中
    Message_iter begin() const {return messages.begin();}
    Message_iter end() const {return messages.end();}
};

Mail_file::Mail_file(const string &file) {
    //打开文件，存入lines
    //在lines中查找邮件，组合起来存入m
    //假定每个邮件以----结束
    ifstream in{file};
    if (!in){
        cerr<<"no"<<file<<'\n';
        exit(1);
    }
    //创建文本行的vector
    for (string s ;  getline(in,s) ; ) {
        lines.push_back(s);
    }
    //创建Message的vector
    auto begin_of_a_message=lines.begin();
    for (auto end_of_a_message=lines.begin(); end_of_a_message != lines.end(); ++end_of_a_message) {
        if (*end_of_a_message == "----"){
            //一封邮件结束
            messages.push_back(Message{begin_of_a_message, end_of_a_message});
            begin_of_a_message=end_of_a_message+1;
        }
    }
}
int is_prefix(const string&s ,const string&p){
    //判断p是不是s的一部分
    int n=p.size();
    if (string(s,0,n)==p)return n;
    return 0;
}
bool find_from_addr(const Message*m,string&s){
    //找到地址行并将地址存入s中
    //找到但地址为空则存入s为""，未找到则返回false
    for (const auto &x:*m) {
        if (int n= is_prefix(x,"From: ")){
            s=string(x,n);
            return true;
        }
    }
    return false;
}
string find_subject(const Message* m){
    //找到邮件主题并返回该主题
    //若没有主题或主题为空，都返回""
    for (const auto&x: *m) {
        if (int n=is_prefix(x,"Subject: "))return string(x,n);
    }
    return "";
}

int main(){
    Mail_file mail_file{R"(D:\MyProgramme\C++_Programming\C++Principles_and_Practise\My_Test_txt\23-2Message.txt)"};
    //将邮件收集在一起，存入一个multimap中
    multimap<string,const Message*>sender;
    for (const auto&m:mail_file) {
        string s;
        if (find_from_addr(&m,s))
            sender.insert(make_pair(s,&m));
    }
    //提取John Doe的邮件主题
    auto pp=sender.equal_range("John Doe <jdoe@machine.example>");
    for (auto p=pp.first;p!=pp.second;++p) {
        cout<<find_subject(p->second)<<"\n";
    }
}