//
// Created by Zhou on 2023/2/5.
//
#include "std_lib_facilities.h"
int main()
{
    cout<<"请输入待查询的单词："<<endl;
    string search;
    cin>>search;
    bool isFound=false;
    ifstream ifs {"D:\\MyProgramme\\C++_Programming\\C++Principles_and_Practise\\My_Test_txt\\11-5Search_for_Words.txt"};
    string Line,line;
    istringstream iss;
    for(int cnt=1;getline(ifs,Line);cnt++)
    {
        line=Line;
        for(char &ch:line)
        {
            switch (ch) {
                case ';':
                case ',':
                case ':':
                case '"':
                case '.':
                    ch=' ';
            }
            if (isalpha(ch))
                ch=tolower(ch);
        }
        iss.clear();
        iss.str(line);
        for(string word;iss>>word;) {
            if (word==search) {
                cout << "行号：" << cnt << "\t\t该行内容：" << Line << endl;
                isFound= true;
            }
        }
    }
    if (!isFound)
        cout<<"NOT FOUND\n";
}