#include"../Head/std_lib_facilities.h"
void print(const vector<int>v)
{
	cout << "Print Vector:\n";
	for (int x : v)
	{
		if (x>0)
		{
			cout << x << '\n';
		}
		else
		{
			cout << "�Ѵ�int��������ֵ��\n";
			break;
		}
	}
}
void fibonacci(const int& first_place, const int& second_place, vector<int>& v, const int& size)
{
	v[0] = first_place;
	v[1] = second_place;
	for (size_t i = 2; i < size; i++)
	{
		v[i] = v[i - 1] + v[i - 2];
	}
}
int main()
{
	cout << "int first_place, int second_place, int size\n";
	int x, y, n;
	cin >> x >> y >> n;
	vector<int>v(n);
	fibonacci(x, y, v, n);
	print(v);
	return 0;
}