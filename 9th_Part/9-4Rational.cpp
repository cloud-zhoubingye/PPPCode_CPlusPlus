#include"../Head/money.h"

Rational::Rational(int numerator, int denominator)
	:numerator{ numerator }, denominator{ denominator }
{
	if (denominator == 0)
	{
		ERROR("Denominator cannot be zero!");
	}
}
double Rational::to_double()
{
	return (double)numerator / denominator;
}
bool operator==(Rational r1, Rational r2)
{
	if (r1.to_double() == r2.to_double())
	{
		return true;
	}
	return false;
}
bool operator!=(Rational r1, Rational r2)
{
	if (r1.to_double() == r2.to_double())
	{
		return false;
	}
	return true;
}
double operator+(Rational r1, Rational r2)
{
	return r1.to_double() + r2.to_double();
}
double operator-(Rational r1, Rational r2)
{
	return r1.to_double() - r2.to_double();
}
double operator*(Rational r1, Rational r2)
{
	return r1.to_double() * r2.to_double();
}
double operator/(Rational r1, Rational r2)
{
	return r1.to_double() / r2.to_double();
}
double operator%(Rational r1, Rational r2)
{
	return r1.to_double() - int(r1.to_double() / r2.to_double()) * r2.to_double();
}
ostream& operator<<(ostream& os, Rational r)
{
	return os << r.to_double();
}
void Rational::operator=(const Rational& r)
{
	numerator = r.numerator;
	denominator = r.denominator;
}