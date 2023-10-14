//
// Created by Zhou on 2023/2/1.
//
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<stdexcept>
using namespace  std;
inline void error(string s){throw std::runtime_error(s);}
template<class T>
char* as_bytes(T&x)
{
    return &reinterpret_cast<char&>(x);
}
int main()
{
    try
    {
        ifstream ifs{ "D:\\MyProgramme\\C++_Programming\\C++Principles_and_Practise\\11-1Binary_Read.txt",ios_base::binary };
        if (!ifs)
        {
            error("Can't open file!");
        }
        ifs.seekg(1);
        ofstream ofs{ "D:\\MyProgramme\\C++_Programming\\C++Principles_and_Practise\\11-1Binary_Write.txt" ,ios_base::binary };
        if (!ofs)
        {
            error("Can't write file!");
        }
        vector<int>v;
        for (int x; ifs.read(as_bytes(x), sizeof(int)); )
        {
            v.push_back(x);
        }
        //
        for (int x : v)
        {
            ofs.write(as_bytes(x), sizeof(int));
        }
    }
    catch (const std::exception&e)
    {
        cerr << "WRONG: " << e.what() << endl;
    }
}