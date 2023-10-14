#include"../Head/std_lib_facilities.h"
int main()
{
	int N = 0;
	cout << "������һ����������ڵ���2�����ҽ������2����֮�������������\n";
	cin >> N;
	vector<int> primes;
	primes.push_back(2);
	for (size_t i = 3; i <= N; i++)
	{
		bool isPrime = true;
		for (size_t j = 0; j < primes.size(); j++)
		{
			if (i%primes[j]==0)
			{
				isPrime = false;
			}
		}
		if (isPrime)
		{
			primes.push_back(i);
		}
	}
	for (size_t i = 0; i < primes.size(); i++)
	{
		cout << primes[i]<<'\n';
	}
}