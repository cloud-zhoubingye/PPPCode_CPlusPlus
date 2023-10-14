/************************************************************************************************************************************
* 
* 计算器2.0版本
*
* 本计算器可以一次运行多次进行计算器操作
* 本计算器允许连加连减，以及连加连减中带有乘除，但不能处理取余
* 本计算器允许阶乘，但必须使用(即英文输入状态下的)半角‘!’
* 本计算器允许()、{}的使用来表示优先级
* 本计算器允许求幂次^，但是其与阶乘混用时请务必加括号()
* 本计算器使用时输入‘=’并换行以终止输入，输入‘q’以终止程序(此功能暂时不能实现)
*
************************************************************************************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
inline void keep_window_open();
void error(string s);

//输入后存储类型和输入流的实现
class Token
{
public:
	char kind;
	double value;
};
class Token_stream
{
public:
	//获取一个Token单词
	Token get();
	//放回一个单词
	void putback(Token t);

private:
	//缓存区内是否有单词
	bool isfull{ false };
	//存储放回单词的缓冲区
	Token buffer;
}
tokenstream;
void Token_stream::putback(Token t)
{
	if (isfull)
	{
		//避免连续两次putback()而没有get()
		error("putback() into a full buffer!");
	}
	else
	{
		buffer = t;
		isfull = true;
	}
}
Token Token_stream::get()
{
	if (isfull)
	{
		isfull = false;
		return buffer;
	}
	else
	{
		char ch;
		cin >> ch;
		switch (ch)
		{
		case '=':
			//立即输出结果
		case 'q':
			//立即退出
		case '(':
		case ')':
		case '{':
		case '}':
		case '+':
		case '-':
		case '*':
		case '/':
		case '!':
		case '^':
			{
				Token t;
				t={ ch,0 };
				return t;
			}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':							//可能输入了小数
		{
			//将刚刚读入的内容放回标准输入流
			cin.putback(ch);
			double value;
			cin >> value;
			Token t;
			t = { 'N',value };
			return t;
		}
		default:
			error("Bad input!");
			break;
		}
	}
}

//实现文法规则：分析器
double expression();
double term();
double middle();
double primary(Token t);

double expression()
/*
Expression表达式的文法规则：
	Term
	Expression '+' Term
	Expression '-' Term
*/
{
	double left_data = term();
	Token t = tokenstream.get();
	for ( ; ; )
	{
		switch (t.kind)
		{
		case '+':
			left_data += term();
			t = tokenstream.get();
			break;
		case '-':
			left_data -= term();
			t = tokenstream.get();
			break;
		default:
			tokenstream.putback(t);
			return left_data;
		}
	}
}
double term()
/*
Term项的文法规则：
	Primary
	Term '*' Primary
	Term '/' Primary
	Term '%' Primary
*/
{
	double left_data = middle();
	Token t = tokenstream.get();
	for ( ; ; )
	{
		switch (t.kind)
		{
		case '*':
			left_data *= middle();
			t = tokenstream.get();
			break;
		case '/':
			{
				double divisor = middle();
				if (divisor != 0)
				{
					left_data /= divisor;
					t = tokenstream.get();
				}
				else
				{
					error("Divide by zero!");
				}
			}
			break;
		default:
			tokenstream.putback(t);
			return left_data;
			break;
		}
	}
}
double middle()
/*
Middle基本表达式的文法规则
	primary
	'(' Expression ')'
	'(' Expression ')'!
	'(' Expression ')'^'(' Expression ')'
*/
{	
	//number是get_token函数可以直接读取到的内容
	Token t = tokenstream.get();
	for ( ; ; )
	{
		switch (t.kind)
		{
		case '{':
		{
			double expr = expression();
			t = tokenstream.get();
			if (t.kind == '}')
			{
				Token token = { 'N',expr };
				expr = primary(token);
				return expr;
			}
		}
		case '(':
		{
			double expr = expression();
			t = tokenstream.get();
			if (t.kind == ')')
			{
				Token token = { 'N',expr };
				expr = primary(token);
				return expr;
			}
		}
		case 'N':
			return primary(t);
		default:
			error("Middle input illegal !");
		}
	}
}
double primary(Token t)
/*
Primary基本表达式的文法规则
	Number
	expression!
	expression^expression
*/
{
	char next;
	cin >> next;
	if (next == '!')
	{
		double ret = t.value - (int)t.value;
		if (ret == 0)
		{
			//t.kind内存储的是一个整数
			int num = (int)t.value;
			int result = 1;
			//计算阶乘
			for (int i = num; i >= 1; i--)
			{
				result *= i;
			}
			return result;
		}
		else
		{
			error("Factorial only allows integers!");
		}
	}
	else if (next=='^')
	{
		double order = expression();
		return pow(t.value, order);
	}
	else 
	{
		//退回给cin输入流
		cin.putback(next);
		return t.value;
	}
}
void error(string s)
{
	throw runtime_error(s);
}
inline void keep_window_open()
{
	char ch;
	cin >> ch;
}
int main()
{
	try
	{
		double exp{ 0 };
		while (cin)
		{
			Token t = tokenstream.get();
			if (t.kind=='q')
			{
				//退出
				break;
			}
			else if(t.kind=='=')
			{
				//立即输出结果
				cout << exp << '\n';
			}
			else
			{
				//读到了一个数值
				tokenstream.putback(t);
			}
			exp = expression();
		}
		keep_window_open();
		return 0;
	}
	catch (const std::exception& err)
	{
		cerr << "ERROR: " << err.what() << '\n';
		keep_window_open();
		return 1;
	}
}
