#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>

using namespace std;
inline void keep_window_open() { char ch; cin >> ch; }

vector<int> num;
int cnt = 0;

void interpretation_rule();
bool isrepetited(int number);
void random_number();
vector<int> user_input(vector<int> guess_num);
int bull_result(vector<int> guess_num);
int cow_result(vector<int> guess_num);
bool is_guess_right(vector<int> guess_num);

void interpretation_rule()
{
	cout << "�����ҽ�Ϊ��������Ϸ����\n"
		<< "�һ��������4��������ͬ�����ֹ���һ����λ����\n"
		<< "Ȼ������Ҫ���в²⣬���������Ĳ²�����\n"
		<< "�����n�����ֲ²���ֵ��ȷ����λ��Ҳ����ȷ�ģ��һ�����㡰nͷ��ţ����\n"
		<< "�����n�����ֲ²���ֵ��ȷ����λ�ò��ԣ��һ�����㡰nͷĸţ����\n"
		<< "�����Է����ز£�ֱ������Ϊֹ��\n";
}

bool isrepetited(int number)
{
	bool isRepetited = false;
	for (size_t i = 0; i < num.size(); i++)
	{
		if (number == num[i])
		{
			isRepetited = true;
			break;
		}
	}
	return isRepetited;
}

void random_number()
{
	srand((unsigned)time(NULL));
	int number = 0;
	for ( ; num.size() < 4; )
	{
		number = rand() % 10;
		if (!isrepetited(number))
		{
			num.push_back(number);
		}
	}
}

vector<int> user_input(vector<int> guess_num)
{
	vector<int> inverted_order_num;
	cout << "�����²��ҵ���λ����ֵΪ����(ÿλ���ֲ����ظ�!)��\n";
	int input = 0;
	cin >> input;
	if (cin)
	{
		//��������ת�����ĸ�0-9����
		for (; input != 0; input /= 10)
		{
			int digit_position = input % 10;
			inverted_order_num.push_back(digit_position);
		}
		//����Ϊ0123,��ô��������һλӦΪ0,��ʵ����û��
		if (inverted_order_num.size()!=4)
		{
			for (size_t i = inverted_order_num.size(); i < 4; i++)
			{
				inverted_order_num.push_back(0);
			}
		}
		//���������
		for (int i = inverted_order_num.size() ; i > 0; i--)
		{
			guess_num.push_back(inverted_order_num[i-1]);
		}
	}
	else
	{
		throw runtime_error("�Բ�������������Ч��\n");
	}
	return guess_num;
}

int bull_result(vector<int> guess_num)
{
	//��ţ����
	int bull = 0;
	for (size_t i = 0; i < num.size(); i++)
	{
		if (num[i]==guess_num[i])
		{
			bull++;
		}
	}
	return bull;
}

int cow_result(vector<int> guess_num)
{
	//ĸţ����
	int cow = 0;
	for (size_t i = 0; i < num.size(); i++)
	{
		for (size_t j = 0; j < guess_num.size(); j++)
		{
			if (num[i] == guess_num[j])
			{
				//����ȣ�������ĸţ
				if (i != j)
				{
					cow++;
					break;
				}
				//Ҳ�����ǹ�ţ
				else
				{
					break;
				}
			}
		}
	}
	return cow;
}

bool is_guess_right(vector<int> guess_num)
{
	int bull_number = bull_result(guess_num);
	cout << bull_number << "ͷ��ţ" << '\t';
	int cow_number = cow_result(guess_num);
	cout << cow_number << "ͷĸţ" << '\n';
	if (bull_number == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	try
	{
		//���͹���
		interpretation_rule();
		//�����ʼ���ĸ���
		random_number();
		//�û��²�
		for (; ; )
		{
			cnt++;
			vector<int> guess_num;
			guess_num=user_input(guess_num);
			if (is_guess_right(guess_num))
				break;						//�ɹ�
			else  continue; 				//�����²�
		}
		cout << "��ϲ���²�ɹ���\n��һ������" << cnt << "�β²�ﵽ�ɹ���\n";
		return 0;
	}
	catch (const std::exception& err)
	{
		cout << "ERROR��" << err.what() << '\n';
		keep_window_open();
		return -1;
	}
}