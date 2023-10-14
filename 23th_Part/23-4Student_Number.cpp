//
// Created by Zhou on 03/05/2023.
//
#include "regex"
#include "iostream"
#include "fstream"
using namespace std;
inline void error(const string& s){throw runtime_error(s);}
inline void error(const string& s, const string& s2){error(s + s2);}
//验证表格布局是否正确

int main(){
    regex header_pat{R"(^[\w ]+(    [\w ]+)$)"};
    regex data_pat{R"(^[\w ]+(\s+\d+){3}$)"};   //正确
    ///\attention
    ///错误：\n
    ///    regex header_pat{R"(^[\\w ]+(    [\\w ]+){3}$)"}\n
    ///    regex data_pat{R"(^[\\w ]+(\\s\\d+){3}$)"};\n
    ///为什么重复一次就正确而三次是错误的？

    try {
        ifstream ifs{"../My_Test_txt/23-4Stu_num.txt"};
        if(!ifs)error("no input files!");
        string line;
        int cnt_line=0;
        //检查文件头行
        if (getline(ifs,line)){
            smatch matches;
            if (!regex_match(line,matches,header_pat))
                error("no or wrong header!");
            else
                cout<<"Header line matches!\nHeader: "<<matches[0]<<endl;
        }
        //检查数据行
        while (getline(ifs,line)){
            ++cnt_line;
            smatch matches;
            if (!regex_match(line,matches,data_pat))
                error("bad data line : line_cnt(", to_string(cnt_line)+")  "+line);
            else
                cout<<"Data line "+ to_string(cnt_line)+" matches!\nLine: "<<matches[0]<<endl
                <<"\tsub matches: "<<matches[1]<<endl

        }
    }
    ///\attention
    ///匹配的子模式应该是第二、三、四栏目的数字
    ///\n 但为什么发现子模式只匹配了第四栏目
    ///\n 如以下输出结果：\n
    ///Line: 0A  12  11  23 \n sub matches:  23
    catch (exception&e) {
        cerr<<e.what()<<endl;
    }
}