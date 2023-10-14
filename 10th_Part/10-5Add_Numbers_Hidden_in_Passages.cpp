#include"../Head/std_lib_facilities.h"
int main()
{
	ifstream ifs{ "D:\\My_C++_Programme\\C++������ƣ�ԭ����ʵ��\\10-5����ȡ���Ķ�.txt" };
	if (!ifs)
	{
		error("can't open file");
	}
	vector<double>num;
	char ch = 0;
	double number = 0;
	long double sum = 0;
	for (; ifs >> ch;)
	{
		if (ch >= '0' && ch <= '9')
		{
			ifs.putback(ch);
			ifs >> number;
			num.push_back(number);
		}
	}
	for (double x : num)
	{
		sum += x;
	}
	cout << "Sum is " << sum << '\n';
}