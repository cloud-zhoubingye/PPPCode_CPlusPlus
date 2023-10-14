#include"../Head/money.h"
#include<stdlib.h>

Money::Money(char type,int value)
	:Type{ ' ' },Cent {0}, Rmb{ 0 }
{
	if (value < 0)
	{
		ERROR("THE VALUE OF MONEY MUST ABOVE ZERO!");
	}
	if (type=='$')
	{
		Type = '$';
		Cent = value;
	}
	if (type=='R')
	{
		Type = 'R';
		Rmb = value;
	}
}
Money::Money()
	:Type{ ' ' }, Cent{ 0 }, Rmb{ 0 }
{
}
void Money::change(char ch_type)
{
	//�ų�����
	if (Type==' ')
	{
		ERROR("NOT INITIAL BEFORE EXCHANGE!");
	}
	if (ch_type==Type)
	{
		ERROR("CANNOT CHANGE A SAME TYPE!");
	}
	//ת��
	if (ch_type=='$')
	{
		double value = Rmb * RMB_to_DOLLAR_rate();
		Cent = si_she_wu_ru(value);
		Rmb = 0;
		Type = '$';
	}
	else
	{
		double value = Cent * DOLLAR_to_RMB_rate();
		Rmb = si_she_wu_ru(value);
		Cent = 0;
		Type = 'R';
	}
}
void Money::operator=(const Money m)
{
	Type = m.type();
	Cent = m.cent();
	Rmb = m.RMB();
}
istream& operator>>(istream& is, Money& money)
{
	cout << "Input like $34.576 or R34.576\nPlease Input:\n";
	double input;
	char ch_type;
	cin.clear();
	cin.sync();
	is >> ch_type;
	if (ch_type == 'q')
	{
		exit(0);
	}
	is >> input;
	if (!cin)
	{
		ERROR("INPUT WRONG!");
	}
	if (ch_type!='R'&&ch_type!='$')
	{
		ERROR("INPUT FORMATION INVALID!");
	}
	double value = input * 100;
	double ret = value - int(value);
	int myvalue;
	if (ret < 0.5)
	{
		myvalue = int(value);
	}
	else
	{
		myvalue = int(value) + 1;
	}
	money = Money{ ch_type,myvalue};
	return is;
}
ostream& operator<<(ostream& os, const Money money)
{
	if (money.type() == ' ')
	{
		ERROR("NOT INITIAL!");
	}
	if (money.type()=='$')
	{
		long long int value = money.cent();
		long long int dollar = value / 100;
		long long int cent = value % 100;
		os << money.type() << dollar << '.' << cent << '\n';
	}
	else if(money.type()=='R')
	{
		long long int value = money.RMB();
		long long int dollar = value / 100;
		long long int cent = value % 100;
		os << "��" << dollar << '.' << cent << '\n';
	}
	return os;
}
long long int si_she_wu_ru(double value)
{
	double ret = value - int(value);
	if (ret < 0.5)
	{
		value = int(value);
	}
	else
	{
		value = int(value) + 1;
	}
	return value;
}
double RMB_to_DOLLAR_rate()
{
	static const double rate= Rational{ 10000,67750 }.to_double();
	return rate;
}
double DOLLAR_to_RMB_rate()
{
	static const double rate=Rational{ 67750,10000 }.to_double();
	return rate;
}

int main()
{
	for (;;)
	{
		try
		{
			Money m1;
			cin >> m1;
			cout << "ת��Ϊ��\n";
			char ch;
			cin >> ch;
			m1.change(ch);
			cout << m1 << '\n';
		}
		catch (const std::exception& e)
		{
			cerr << "ERROR: " << e.what() << "\n\n";
		}
	}
}