#include"../Head/std_lib_facilities.h"
int main()
{
	constexpr double pi = 3.1415926;
	int n = 0;
	cin >> n;
	const double Pi= pi * n;
	cout << Pi << '\n' << pi;
}