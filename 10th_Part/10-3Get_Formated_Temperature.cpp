#include<iostream>
#include<iomanip>
#include<stdbool.h>
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
using namespace std;
inline void error(string s) { throw runtime_error(s); }
inline void end_of_loop(ifstream& is, char terminal, const string& message) { if (is.fail()) { is.clear(); char ch; if (is >> ch || ch == terminal) { return; } else { error(message); } } }
inline void end_of_loop(istream& is, char terminal, const string& message) { if (is.fail()) { is.clear(); char ch; if (is >> ch || ch == terminal) { return; } else { error(message); } } }
//非读数
constexpr int not_a_reading = -9999, not_a_year = -9999,not_a_month = -9999, not_a_day = -9999, temp_lowest = -100, temp_highest = 100;
//如果一开始读入格式不正确
void clear_up_mess(ifstream& is)
{
	is.unget();
	is.clear(ios_base::failbit);
}
//Day
struct Day
{
	//总共0-23个小时
	vector<double>hour{ vector<double>(24,not_a_reading) };
};
//Month
struct Month
{
	int month{ not_a_month };
	//总共1-31天,0废弃不用
	vector<Day>day{ 32 };
};
//Year
struct Year
{
	int year{ not_a_year };
	//总共1-12天,0废弃不用
	vector<Month>month{ 13 };
};
//Reading
struct Reading
{
	int day{ not_a_reading };
	int hour{ not_a_reading };
	double temperature{ not_a_reading };
};
//类型string与int互相转化
vector<string>standard_month_table = { "jan","feb" ,"mar" ,"apr","may","jun","jul","aug","sep","oct","nov","dec" };
int month_string_to_int(string month)
{
	for (int i = 0; i < 12; i++)
	{
		if (month == standard_month_table[i])
		{
			return i+1;
		}
	}
	error("Bad month in English!");
}
string month_int_to_string(int month)
{
	if (month < 1 || month>12)
	{
		error("Bad month that out of range!");
	}
	return standard_month_table[month - 1];
}
//重载输入运算符Reading
ifstream& operator>>(ifstream& is, Reading& r)
{
	char ch1;
	//如果不是Reading
	if ((is >> ch1 && ch1 != '(')||!is)
	{
		clear_up_mess(is);
		return is;
	}
	//如果是Reading
	int input_date{ not_a_reading };
	int input_hour{ not_a_reading };
	double input_temp{ not_a_reading };
	char ch2;
	is >> input_date >> input_hour >> input_temp >> ch2;
	if (!is||ch2!=')')
	{
		error("Bad end of temperature!");
	}
	r.day = input_date;
	r.hour = input_hour;
	r.temperature = input_temp;
	return is;
}
//检测Reading是否合法
bool reading_isvalid(Reading r)
{
	if (r.day<1||r.day>31)
	{
		return false;
	}
	if (r.hour<0||r.hour>23)
	{
		return false;
	}
	if (r.temperature<temp_lowest||r.temperature>temp_highest)
	{
		return false;
	}
	return true;
}
//重载输入运算符Month
ifstream& operator>>(ifstream& is, Month& m)
{
	char ch1;
	//如果读入格式不是Month
	if ((is >> ch1 && ch1 != '{')||(!is))
	{
		clear_up_mess(is);
		return is;
	}
	//如果读入格式是Month
	string month_mark;
	if ((is >> month_mark && month_mark != "month")||!is)
	{
		error("Bad start of month!");
	}
	string input_month;
	is >> input_month;
	m.month = month_string_to_int(input_month);
	for (Reading r; is >> r;)
	{
		if (reading_isvalid(r))
		{
			//如果日期时间曾已经读入过
			if (m.day[r.day].hour[r.hour]!=not_a_reading)
			{
				error("Repeated temperatures!");
			}
			//如果对应的日期时间未曾读入过，存入数据
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
		{
			error("Invalid date!");
		}
	}
	end_of_loop(is, '}', "Bad end of month!");
	return is;
}
//重载判等运算符Day
bool operator==(Day d1, Day d2)
{
	if (d1.hour==d2.hour)
	{
		return true;
	}
	return false;
}
bool operator!=(Day d1, Day d2)
{
	if (d1.hour == d2.hour)
	{
		return false;
	}
	return true;
}
//重载输入运算符Year
ifstream& operator>>(ifstream& is, Year& y)
{
	//如果格式错误
	char ch;
	is >> ch;
	if (ch!='{')
	{
		clear_up_mess(is);
		return is;
	}
	//如果格式正确
	string year_mark;
	is >> year_mark;
	if (!is||year_mark!="year")
	{
		error("Bad start of year!");
	}
	int input_year;
	is >> input_year;
	y.year = input_year;
	for (Month m; is >> m;)
	{
		if (y.month[m.month].month!=not_a_month)
		{
			error("Repeated months!");
		}
		y.month[m.month] = m;
		m = Month{};
	}
	end_of_loop(is, '}', "Bad end of year!");
	return is;
}
//重载输出运算符
ofstream& operator<<(ofstream& os, Year& y)
{
	//Year
	os << "Year: " << y.year << '\n';
	//Month
	for (int i = 1; i < 13; i++)
	{
		if (y.month[i].month!=not_a_month)
		{
			os << "Month: " << month_int_to_string(y.month[i].month) << '\n';
			//Day
			for (int j = 1; j < 32; j++)
			{
				if (y.month[i].day[j]!=Day{})
				{
					os << "Day: " << j << '\n';
					//Hour
					for (int k = 0; k < 24; k++)
					{
						if (y.month[i].day[j].hour[k]!=not_a_reading)
						{
							os << "Hour: " << j << '\n';
							//Temperature
							os << "Temperature: " << y.month[i].day[j].hour[k] << '\n';
						}
					}
				}
			}
		}
	}
	os << '\n';
	return os;
}
int main()
{
	//初始化文件输入
	ifstream ist{ "D:\\My_C++_Programme\\C++程序设计：原理与实践\\10-3待读取的格式化温度值.txt" };
	if (!ist) { error("Cannot open this file !"); }
	//初始化文件输出
	ofstream ost{ "D:\\My_C++_Programme\\C++程序设计：原理与实践\\10-3输出的格式化温度值.txt" };
	if (!ost) { error("Cannot write this file !"); }

	//主程序
	try
	{
		Year myyear1;
		ist >> myyear1;
		ost << myyear1;
		Year myyear2;
		ist >> myyear2;
		ost << myyear2;
		Year myyear3;
		ist >> myyear3;
		ost << myyear3;
	}
	catch (const std::exception&e)
	{
		cerr << "ERROR:　" << e.what();
	}

	//关闭文件
	ost.close();
}