/************************************************************************************************************************************
*
* ������3.0�汾
*
* 
* ʹ��˵����
*
* ������������һ�����ж�ν��м���������
* ����������������ʾ��>������(Ӣ������״̬�µ�)��;������������ֹ����
* ���������������������;�����룬Ч���뵥����;����ͬ
* ��������������һ�ж��������ʽ����
* �����������������������Լ����������д��гˡ�����ȡ��
* ���������Ը�����Ҳ����ȡ��(ģ)�����㷽��Ϊx%y=x-y*int(x/y)
* ������������һԪ�Ӽ��������-������+��������--��ʾ����ȡ������
* ������������׳ˣ�������ʹ��(��Ӣ������״̬�µ�)��ǡ�!��
* ������������()��{}��ʹ������ʾ���ȼ�
* ���������������ݴ�^����������׳˻���ʱ����ؼ�����()
* ��������ʹ��ʱ���롮q������ֹ����(�˹�����ʱ����ʵ��)
* ������˳�����ϣ������ʹ�ñ�������ʱ��������(Ӣ������״̬�µ�)��;���Լ���
* ������˳���������ʱ�������롰~���Թرմ���
* ��������֧���Զ�����������ǲ�֧��δ��ʼ���ı�������δʵ�֣�
* ���������Ѿ�Ԥ����������1����pi��e����ֱ��ʹ��
*
*
* ʵ�ּ��������ܵ��ķ�����
* Expression��
	Term
	Expression '+' Term
	Expression '-' Term
* Term��
	Primary
	Term '*' Middle
	Term '/' Middle
	Term '%' Middle
* Middle��
	primary
	'(' Expression ')'
	'(' Expression ')'!
	'(' Expression ')'^'(' Expression ')'
	��+�� Expression
	��-�� Expression
* Primary��
	Number
	expression!
	expression^expression
* 
* 
* ʵ�ֱ������幦�ܵ��ķ�����
* Calculation:
	statement
	print
	quit
	calculation statement
* Statement:
	declaration
	expression
* Declaration:
	"let" name "=" Expression
* 
* 
************************************************************************************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
//��������
const char NUMBER = 'N';
const char QUIT = 'q';
const char PRINT = ';';
const char EXIT = '~';
const string PROMPT = "> ";
const char DEFINE = '=';
const char NAME = 'a';
const char LET = 'L';
const string DECLARATION_KEY = "let";

//�����洢���ͺ�������������ʵ��
class Token
{
public:
	char kind;
	double value = 0;
	string name;
	Token(char ch) :kind{ ch } {};
	Token(char ch, double val) :kind{ ch }, value{ val } {};
	Token(char ch, string s) :kind{ ch }, name{ s } {};
};
class Token_Stream
{
public:
	//��ȡһ��Token����
	Token get();
	//�Ż�һ������
	void putback(Token t);
	//���ֱ���ַ�ch�������ַ�
	void cleanup_mess(char ch);

private:
	//���������Ƿ��е���
	bool isfull{ false };
	//�洢�Żص��ʵĻ�����
	Token buffer=Token(' ',0);
};
Token_Stream tokenstream;

//�������������ʵ��
class Variable 
{
public:
	string name;
	double value;
};
vector<Variable>var_table;

//ʵ�ּ����������ķ�����ķ�������������
double expression();
double term();
double middle();
double primary(Token t);

//ʵ�ֱ�������ĺ�������
double get_value(string get_name);
void set_value(string set_name, double set_value); 
double statement();
double declaration();
bool isAlpha(char ch);
bool isDigit(char ch);
double define_name(string variable, double value);
bool is_declared(string variable);

//������������
inline void keep_your_window_open(char ch);
void error(string s);
void calculate();
void clean_up_mess();
void error_handling();

//�����洢���ͺ������������͵���غ���ʵ��
void Token_Stream::putback(Token t)
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
Token Token_Stream::get()
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
		case PRINT:		//����������
		case QUIT:		//�����˳�
		case DEFINE:
		case '(':
		case ')':
		case '{':
		case '}':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '!':
		case '^':
		{
			Token t = { ch,0 };
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
			Token t = { NUMBER,value };
			return t;
		}
		default:
			if (isAlpha(ch))
			{
				string s;
				cin >> s;
				s += ch;
				while (cin.get(ch)&&(isAlpha(ch)||isDigit(ch)))
				{
					s + ch;
				}
				cin.putback(ch);
				if (s==DECLARATION_KEY)
				{
					return Token(LET);
				}
				else
				{
					Token t = { NAME,s };
					return t;
				}
			}
			else
			{
				error("Bad input!");
			}
		}
	}
}
void Token_Stream::cleanup_mess(char ch)
{
	//���Ȳ鿴������
	if (isfull&&(ch==buffer.kind))
	{
		isfull = false;
		return;
	}
	else
	{
		isfull = false;
		//���Ҳ����ղ���Ҫ�Ĵ�����
		char ch_rubbish;
		while (cin>>ch_rubbish)
		{
			if (ch_rubbish==ch)
			{
				return;
			}
		}
	}
}

//ʵ�ּ����������ķ�����ķ���������ʵ��
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
	Term '*' Middle
	Term '/' Middle
	Term '%' Middle
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
		case '%':
			{
				double divided = middle();
				if (divided==0)
				{
					error("Calculating residue(Mod) by zero!");
				}
				else
				{
					left_data = fmod(left_data, divided);
					t = tokenstream.get();
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
	��+�� Expression
	��-�� Expression
*/
{
	//number��get_token��������ֱ�Ӷ�ȡ��������
	Token t = tokenstream.get();
	for (; ; )
	{
		switch (t.kind)
		{
		case '{':
		{
			double expr = expression();
			t = tokenstream.get();
			if (t.kind == '}')
			{
				Token token = { NUMBER, expr };
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
				Token token = { NUMBER,expr };
				expr = primary(token);
				return expr;
			}
		}
		case NUMBER:
			return primary(t);
		case '+':
			return middle();
		case '-':
			return -middle();
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
	else if (next == '^')
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

//ʵ�ֱ�������ĺ���ʵ��
double get_value(string get_name)
{
	for (const Variable v : var_table)
	{
		if (v.name==get_name)
		{
			return v.value;
		}
	}
	error("Get: undefined variable!");
}
void set_value(string set_name, double set_value)	
{
	/*��������set_name�ı���ֵΪset_value*/
	for (Variable v : var_table)
	{
		if (set_name==v.name)
		{
			v.value = set_value;
			return;
		}
	}
	error("Set: undefined variable!");
}
double statement()
{
	Token t = tokenstream.get();
	switch (t.kind)
	{
	case LET:
		return declaration();
	default:
		tokenstream.putback(t);
		return expression();
	}
}
double declaration()
{
	Token t = tokenstream.get();
	if (t.kind!=NAME)
	{
		error("Name expected in declaration!");
	}
	else
	{
		string var_name = t.name;
		Token t1 = tokenstream.get();
		if (t1.kind!='=')
		{
			error("��=�� is missing in the declaration!");
		}
		else
		{
			double value = expression();
			define_name(var_name, value);
			return value;
		}
	}
}
bool is_declared(string variable)
{
	for (Variable v : var_table)
	{
		if (v.name==variable)
		{
			return true;
		}
	}
	return false;
}
bool isAlpha(char ch)
{
	if (ch>='a'&&ch<='z')
	{
		return true;
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isDigit(char ch)
{
	if (ch>='0'&&ch<='9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
double define_name(string variable,double value)
{
	if (is_declared(variable))
	{
		error("Variable declared twice!");
	}
	else
	{
		Variable v{ variable,value };
		var_table.push_back(v);
		return value;
	}
}

//��������ʵ��
void error(string s)
{
	throw runtime_error(s);
}
inline void keep_your_window_open(char ch_exit)
{
	cout << "Please enter character ��" << ch_exit << "�� to close the window!\n";
	for (char ch; cin >> ch; )
	{
		if (ch==ch_exit)
		{
			break;
		}
	}
}
void clean_up_mess()
{
	tokenstream.cleanup_mess(PRINT);
}
void calculate()
{
	cout << PROMPT;
	Token t = tokenstream.get();
	while (t.kind == PRINT)
	{
		/*�Ե�=���ţ���t.kind��Ϊ��һ��������Ϊq��
		�Ӷ��ٴν��ж�q�ļ�飬���⽫q��Ϊmiddle���뱨��*/
		t = tokenstream.get();
	}
	if (t.kind == QUIT)
	{
		//�˳�
		return;
	}
	//��������һ�������˻�ȥ
	tokenstream.putback(t);
	cout << "RESULT: " << statement() << '\n';
}
void error_handling()
{
	while (cin)
	{
		try
		{
			calculate();
		}
		catch (const std::exception&err)
		{
			cerr << "ERROR: " << err.what() << '\n';
			cout << "Enter ��;�� to continue!\n";
			clean_up_mess();
		}
	}
}
int main()
{
	try
	{
		define_name("pi", 3.1415926535);
		define_name("e", 2.7182818284);
		error_handling();
		keep_your_window_open('~');
		return 0;
	}
	catch (const std::exception& err)
	{
		cerr << "ERROR: " << err.what() << '\n';
		keep_your_window_open('~');
		return 1;
	}
}
