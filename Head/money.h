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
class Rational
{
public:
	Rational(int numerator, int denominator);
	double to_double();
	void operator=(const Rational& r);
	
private:
	 int numerator;
	 int denominator;
};
extern bool operator==(Rational r1, Rational r2);
extern bool operator!=(Rational r1, Rational r2);
extern double operator+(Rational r1, Rational r2);
extern double operator-(Rational r1, Rational r2);
extern double operator*(Rational r1, Rational r2);
extern double operator/(Rational r1, Rational r2);
extern double operator%(Rational r1, Rational r2);
extern ostream& operator<<(ostream& os, Rational r);

class Money
{
public:
	Money(char type,int value);
	Money();
	long long int cent()const { return Cent; }
	long long int RMB()const { return Rmb; }
	char type()const { return Type; }
	void operator=(const Money m);
	void change(char ch_type);
private:
	char Type;
	//美元：分
	long long int Cent;
	//人民币：分
	long long int Rmb;
};
double RMB_to_DOLLAR_rate();
double DOLLAR_to_RMB_rate();
long long int si_she_wu_ru(double value);
ostream& operator<<(ostream& os, const Money money);
istream& operator>>(istream& is, Money& money);