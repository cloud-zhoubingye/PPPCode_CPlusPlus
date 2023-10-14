#include"../Head/std_lib_facilities.h"
void print(const vector<int>& v)
{
	cout << "Print Vector: \n";
	for (int x : v)
	{
		cout << x << '\n';
	}
}
void SWAP(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void input(vector<int>&v)
{
	int x;
	while (cin>>x)
	{
		v.push_back(x);
	}
}
vector<int> reversal_newone(const vector<int>& v)
{
	vector<int>v1;
	for (int i = v.size()-1; i >=0; i--)
	{
		v1.push_back(v[i]);
	}
	return v1;
}
void reversal_oldone(vector<int>& v)
{
	//���ܱ������������ε���û�л���
	for (int i = v.size() - 1; i >= v.size()/2; i--)
	{
		SWAP(v[i], v[v.size() - i - 1]);
	}
}
int main()
{
	vector<int>v0;
	input(v0);
	vector<int>v1 = reversal_newone(v0);
	print(v1);
	reversal_oldone(v0);
	print(v0);
	swap(v0, v1);
	print(v0);
	reverse(v0.begin(), v0.end());
	print(v0);
}