/************************************************************************************************************************************
* 
* ������2.0�汾
*
* ������������һ�����ж�ν��м���������
* �����������������������Լ����������д��г˳��������ܴ���ȡ��
* ������������׳ˣ�������ʹ��(��Ӣ������״̬�µ�)��ǡ�!��
* ������������()��{}��ʹ������ʾ���ȼ�
* ���������������ݴ�^����������׳˻���ʱ����ؼ�����()
* ��������ʹ��ʱ���롮=������������ֹ���룬���롮q������ֹ����(�˹�����ʱ����ʵ��)
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

//�����洢���ͺ���������ʵ��
class Token
{
public:
	char kind;
	double value;
};
class Token_stream
{
public:
	//��ȡһ��Token����
	Token get();
	//�Ż�һ������
	void putback(Token t);

private:
	//���������Ƿ��е���
	bool isfull{ false };
	//�洢�Żص��ʵĻ�����
	Token buffer;
}
tokenstream;
void Token_stream::putback(Token t)
{
	if (isfull)
	{
		//������������putback()��û��get()
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
			//����������
		case 'q':
			//�����˳�
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
		case '.':							//����������С��
		{
			//���ոն�������ݷŻر�׼������
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

//ʵ���ķ����򣺷�����
double expression();
double term();
double middle();
double primary(Token t);

double expression()
/*
Expression���ʽ���ķ�����
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
Term����ķ�����
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
Middle�������ʽ���ķ�����
	primary
	'(' Expression ')'
	'(' Expression ')'!
	'(' Expression ')'^'(' Expression ')'
*/
{	
	//number��get_token��������ֱ�Ӷ�ȡ��������
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
Primary�������ʽ���ķ�����
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
			//t.kind�ڴ洢����һ������
			int num = (int)t.value;
			int result = 1;
			//����׳�
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
		//�˻ظ�cin������
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
				//�˳�
				break;
			}
			else if(t.kind=='=')
			{
				//����������
				cout << exp << '\n';
			}
			else
			{
				//������һ����ֵ
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
