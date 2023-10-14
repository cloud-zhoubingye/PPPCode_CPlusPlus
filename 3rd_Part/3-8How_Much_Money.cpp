#include"../Head/std_lib_facilities.h"
int main()
{
	cout << "How many pennies(1����Ӳ��) do you have?\n";
	int penny;
	cin >> penny;
	cout << "How many nickels(5����Ӳ��) do you have?\n";
	int nickel;
	cin >> nickel;
	cout << "How many dimes(10����Ӳ��) do you have?\n";
	int dime;
	cin >> dime;
	cout << "How many quarters(25����Ӳ��) do you have?\n";
	int quarter;
	cin >> quarter;
	cout << "How many half-dollars(50����Ӳ��) do you have?\n";
	int half_dollar;
	cin >> half_dollar;
	cout << "How many one-dollars(100����Ӳ��) do you have?\n";
	int one_dollar;
	cin >> one_dollar;
	cout << "\nYou have " << penny << " pennies\n"
			<< "You have " << nickel << " nickels\n"
			<< "You have " << dime << " dimes\n"
			<< "You have " << quarter << " quarters\n"
			<< "You have " << half_dollar << " half-dollars\n"
			<< "You have " << one_dollar << " one-dollars\n\n";
	int sum = penny + 5 * nickel + 10 * dime + 25 * quarter + 50 * half_dollar + 100 * one_dollar;
	double total = sum / 100.0;
	cout << "The value of all your coins is " << sum << " cents\n";
	cout << "The value of all your coins is $" << total << "\n";
	return 0;
}