#include"../Head/std_lib_facilities.h"
int main()
{
	cout << "������һ��ƴд�����֣�\n��Ӣ�ģ�������ten������zero\n";
	string str;
	int num;
	cin >> str;
	if (str == "zero")
	{
		num = 0;
	}
	else if (str == "one")
	{
		num = 1;
	}
	else if (str == "two")
	{
		num = 2;
	}
	else if (str == "three")
	{
		num = 3;
	}
	else if (str=="four")
	{
		num = 4;
	}
	else if (str=="five")
	{
		num = 5;
	}
	else if (str=="six")
	{
		num = 6;
	}
	else if (str=="seven")
	{
		num = 7;
	}
	else if (str=="eight")
	{
		num = 8;
	}
	else if (str=="nine")
	{
		num = 9;
	}
	else if (str=="ten")
	{
		num = 10;
	}
	else
	{
		num = -1;
	}
	if (num!=-1)
	{
		cout << "\nWhat you have already inputed is��\n\n" << num << '\n';
	}
	else
	{
		cout << "\nNot a number I kown!\n";
	}
}