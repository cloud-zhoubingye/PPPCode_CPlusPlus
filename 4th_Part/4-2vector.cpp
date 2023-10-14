#define _CRT_SECURE_NO_WARNINGS 1
#include"../Head/std_lib_facilities.h"
int main()
{
	vector<int> v;
	int num=0,cnt=0;
	do
	{
		scanf("%d", &num);
		v.push_back(num);
		cnt++;
	} while (cnt!=10);

	for (int x:v)
	{
		cout << x <<'\n';
	}
}