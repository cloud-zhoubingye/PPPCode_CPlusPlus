#include"../Head/Date.h"
using namespace std;

namespace Namespace_Date
{
	Date::Date(int year, My_Month month, int day)
		:y{ year }, m{ month }, d{ day }
	{
		if (!is_valid())
		{
			throw Invalid_Date{};
		}
	}
	const Date& default_date()
	{
		static const Date init_date(2000, My_Month::January, 1);
		return init_date;
	}
	Date::Date()
		:y{ default_date().y }, m{ default_date().m }, d{ default_date().d }
	{
	}
	void Date::add_day(int n)
	{

	}
	void Date::add_month(int n)
	{

	}
	void Date::add_year(int n)
	{
		//�����2.29��n�����3.1
		if (m==My_Month::February&&d==29&&!is_leapyear())
		{
			//����n���3.1������һ���2.29
			m = My_Month::March;
			d = 1;
		}
		y += n;
	}
	bool Date::is_valid()const
	{
		if (m<My_Month(0)||m>My_Month(12))
		{
			return false;
		}
		if (y<0)
		{
			return false;
		}
		//��Щ�·ݶ�������31��
		int max_days=31;
		switch (m)
		{
		case Namespace_Date::My_Month::January:
			break;
		case Namespace_Date::My_Month::February:
			if (is_leapyear())
			{
				max_days = 29;
			}
			else
			{
				max_days = 28;
			}
			break;
		case Namespace_Date::My_Month::March:
			break;
		case Namespace_Date::My_Month::April:
			max_days = 30;
			break;
		case Namespace_Date::My_Month::May:
			break;
		case Namespace_Date::My_Month::June:
			max_days = 30;
			break;
		case Namespace_Date::My_Month::July:
			break;
		case Namespace_Date::My_Month::August:
			break;
		case Namespace_Date::My_Month::September:
			max_days = 30;
			break;
		case Namespace_Date::My_Month::October:
			break;
		case Namespace_Date::My_Month::November:
			max_days = 30;
			break;
		case Namespace_Date::My_Month::December:
			break;
		default:
			break;
		}
		if (d<0 || d>max_days)
		{
			return false;
		}
		return true;
	}
	bool Date::is_leapyear()const
	{
		if (y%4==0&&y%100!=0)
		{
			return true;
		}
		if (y%400==0)
		{
			return true;
		}
		return false;
	}
	ostream& operator<<(ostream& outstream, Date date)
	{
		return outstream << "Year: " << date.year() << ','
			<< "Month: " << date.month() << ','
			<< "Day: " << date.day() << '\n';
	}
	istream& operator>>(istream& instream, Date date)
	{
		cout << "���������ڣ���/��/��\n";
		int y, m, d;
		char ch1, ch2;
		instream >> y >> ch1 >> m >> ch2 >> d;
		if (!instream)
		{
			return instream;
		}
		if (ch1 != '/' || ch2 != '/')
		{
			instream.clear(ios_base::failbit);
			return instream;
		}
		date = Date(y, My_Month(m), d);
		return instream;
	}
	What_Day day_of_week(const Date& date)
	{
		//...
		return What_Day::Monday;
	}
	What_Day next_Sunday(const Date& date)
	{
		
		return What_Day::Monday;
	}
	What_Day next_weekday(const Date& date)
	{
		//...
		return What_Day::Monday;
	}
}