#include"../Head/std_lib_facilities.h"
int main()
{
	cout << "��������һ�����������������������������(���߾��ո����)��\n";
	cout << "��������'+'��'-'��'*'��'/'��\n";
	string operation;
	double a, b,sum;
	cin >> operation >> a >> b;
	if (operation=="+")
	{
		sum = a + b;
	}
	else if(operation=="-")
	{
		sum = a - b;
	}
	else if (operation=="*")
	{
		sum = a * b;
	}
	else if (operation=="/")
	{
		sum = a / b;
	}
	else
	{
		cout << "your input is not valid!\n";
		return 0;
	}
	cout << "The result of " << a << " " << operation << " " << b << " is " << sum << '\n';
}