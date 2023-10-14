#include"../Head/std_lib_facilities.h"
string mode;
int times;
void find_mode(vector<string>str,int left,int right)
{
	int center = (left + right) / 2;
	int l = 0, r = 0;
	int cnt = 1;
	for ( l = center-1; l >=left ; l--)
	{
		if (str[l]==str[center])
		{
			cnt++;
		}
		else
		{
			break;
		}
	}
	for ( r = center+1; r <=right; r++)
	{
		if (str[r]==str[center])
		{
			cnt++;
		}
		else
		{
			break;
		}
	}
	if (cnt==times&&str[center]>mode)
	{
		//����ͬ������һ������������������Ǹ�
		times = cnt;
		mode = str[center];
	}
	else if (cnt>times)
	{
		times = cnt;
		mode = str[center];
	}
	if (l-left>times)
	{
		find_mode(str, left, l);
	}
	if (right-r>times)
	{
		find_mode(str, r, right);
	}
}
int main()
{
	vector<string> str;
	string input;
	while (cin>>input)
	{
		str.push_back(input);
	}
	sort(str);
	find_mode(str, 0, str.size() - 1);
	cout << "\nMode: "<<mode << '\t' << "Times: "<<times << '\n';
}