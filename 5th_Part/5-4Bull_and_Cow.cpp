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
	cout << "下面我将为您介绍游戏规则：\n"
		<< "我会随机生成4个互不相同的数字构成一个四位数，\n"
		<< "然后您需要进行猜测，并输入您的猜测结果，\n"
		<< "如果有n个数字猜测数值正确而且位置也是正确的，我会告诉你“n头公牛”，\n"
		<< "如果有n个数字猜测数值正确但是位置不对，我会告诉你“n头母牛”，\n"
		<< "您可以反复地猜，直至猜中为止！\n";
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
	cout << "请您猜测我的四位数数值为多少(每位数字不会重复!)：\n";
	int input = 0;
	cin >> input;
	if (cin)
	{
		//将大整数转换成四个0-9整数
		for (; input != 0; input /= 10)
		{
			int digit_position = input % 10;
			inverted_order_num.push_back(digit_position);
		}
		//可能为0123,那么倒序的最后一位应为0,而实际上没有
		if (inverted_order_num.size()!=4)
		{
			for (size_t i = inverted_order_num.size(); i < 4; i++)
			{
				inverted_order_num.push_back(0);
			}
		}
		//将倒序变正
		for (int i = inverted_order_num.size() ; i > 0; i--)
		{
			guess_num.push_back(inverted_order_num[i-1]);
		}
	}
	else
	{
		throw runtime_error("对不起！您的输入无效！\n");
	}
	return guess_num;
}

int bull_result(vector<int> guess_num)
{
	//公牛个数
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
	//母牛个数
	int cow = 0;
	for (size_t i = 0; i < num.size(); i++)
	{
		for (size_t j = 0; j < guess_num.size(); j++)
		{
			if (num[i] == guess_num[j])
			{
				//有相等，可能是母牛
				if (i != j)
				{
					cow++;
					break;
				}
				//也可能是公牛
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
	cout << bull_number << "头公牛" << '\t';
	int cow_number = cow_result(guess_num);
	cout << cow_number << "头母牛" << '\n';
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
		//解释规则
		interpretation_rule();
		//随机初始化四个数
		random_number();
		//用户猜测
		for (; ; )
		{
			cnt++;
			vector<int> guess_num;
			guess_num=user_input(guess_num);
			if (is_guess_right(guess_num))
				break;						//成功
			else  continue; 				//继续猜测
		}
		cout << "恭喜您猜测成功！\n您一共花费" << cnt << "次猜测达到成功！\n";
		return 0;
	}
	catch (const std::exception& err)
	{
		cout << "ERROR：" << err.what() << '\n';
		keep_window_open();
		return -1;
	}
}