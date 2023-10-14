#include"../Head/std_lib_facilities.h"
int factorial(int num)
{
	if (num==0)
	{
		error("0 is illegal for factorial calculation!");
	}
	int result = 1;
	for (size_t i = 2; i <= num; i++)
	{
		result *= i;
	}
	return result;
}
int permutation()
{
	double number1;
	cin >> number1;
	if (!cin)
	{
		error("Wrong input number!");
	}
	if (number1-(int)number1!=0)
	{
		error("Permutation numbers are allowed only for integers!");
	}
	int num1 = (int)number1;
	double number2;
	cin >> number2;
	if (!cin)
	{
		error("Wrong input number!");
	}
	if (number2 - (int)number2 != 0)
	{
		error("Permutation numbers are allowed only for integers!");
	}
	int num2 = (int)number2;
	return factorial(num1) / factorial(num1 - num2);
}
int combination()
{
	double number1;
	cin >> number1;
	if (!cin)
	{
		error("Wrong input number!");
	}
	if (number1 - (int)number1 != 0)
	{
		error("Combination numbers are allowed only for integers!");
	}
	int num1 = (int)number1;
	double number2;
	cin >> number2;
	if (!cin)
	{
		error("Wrong input number!");
	}
	if (number2 - (int)number2 != 0)
	{
		error("Combination numbers are allowed only for integers!");
	}
	int num2 = (int)number2;
	return factorial(num1) / (factorial(num1 - num2)*factorial(num2));
}
int main()
{
	try
	{
		string mode;
		for (; ; )
		{
			cout << "���롰���С��Խ�������������!\n"
				<< "���롰��ϡ��Խ������������!\n"
				<< "���롰�˳����Խ�������!\n";
			cin.clear();
			cin.sync();
			cin >> mode;
			if (mode == "����")
			{
				cout << "������������a��b���ֱ�����a��ȡb���ķ�����\n"
					<< permutation() << '\n';
			}
			else if (mode == "���")
			{
				cout << "������������a��b���ֱ�����a��ȡb���ķ�����\n"
					<< combination() << '\n';
			}
			else if (mode == "�˳�")
			{
				break;
			}
			else
			{
				error("Wrong mode control input!");
			}
		}
	}
	catch (const std::exception&e)
	{
		cout << "ERROR: " << e.what() << '\n';
	}
	return 0;
}