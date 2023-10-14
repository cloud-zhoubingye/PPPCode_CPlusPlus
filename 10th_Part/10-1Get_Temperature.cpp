#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>
#include<stdbool.h>
using namespace std;
inline void error(string s) { throw runtime_error(s); }
struct Reading
{
	int Hour;
	double Temperature;
};
int main()
{
	try
	{
		ifstream ist{ "D:\\My_C++_Programme\\C++程序设计：原理与实践\\10-1待读取的温度.txt" };
		if (!ist)
		{
			error("Cannot open file !");
		}
		ofstream ost{ "D:\\My_C++_Programme\\C++程序设计：原理与实践\\10-1程序输出的温度.txt" };
		if (!ost)
		{
			error("Cannot write file !");
		}
		vector<Reading>temps;
		int hour;
		double temperature;
		while (ist >> hour >> temperature)
		{
			if (hour < 0 || hour>23)
			{
				error("Hour out of range !");
			}
;			temps.push_back(Reading{ hour,temperature });
		}
		for (size_t i = 0; i < temps.size(); i++)
		{
			ost << '(' <<" 小时: " << temps[i].Hour << " , "<<"温度: "
				<< temps[i].Temperature << " )\n";
		}
		if (!cin)
		{
			if (cin.bad())
			{
				error("Cin stream is bad !");
			}
			if (cin.fail())
			{
				cin.clear();
				//恢复流的其他操作
			}
			if (cin.eof())
			{
				cout << "执行完毕！\n";
			}
		}
	}
	catch (const std::exception&e)
	{
		cerr << "ERROR: " << e.what() << endl;
	}
}