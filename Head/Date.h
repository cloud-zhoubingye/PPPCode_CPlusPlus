#pragma once

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
inline void ERROR(string s) { throw runtime_error(s); }
namespace Namespace_Date
{
	enum class My_Month
	{
		January = 1, February, March, April, May, June, July,
		August, September, October, November, December
	};
	enum class What_Day
	{
		Monday=1,Tuesday,Wendnesday, Thursday,Friday,Saturday,Sunday
	};
	class Date
	{
	public:
		class Invalid_Date { };
		Date(int year, My_Month month, int day);
		Date();
		inline int year() const { return y; }
		inline int month() const { return int(m); }
		inline int day() const { return d; }
		void add_year(int n);
		void add_month(int n);
		void add_day(int n);
		
	private:
		int y;
		My_Month m;
		int d;
		bool is_valid()const;
		bool is_leapyear()const;
	};

	ostream& operator<<(ostream& outstream, Date date);
	istream& operator>>(istream& instream, Date date);
	What_Day day_of_week(const Date& date);
	What_Day next_Sunday(const Date& date);
	What_Day next_weekday(const Date& date);
}