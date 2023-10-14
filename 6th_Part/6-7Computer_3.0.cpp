/************************************************************************************************************************************
*
* 计算器3.0版本
*
* 
* 使用说明：
*
* 本计算器可以一次运行多次进行计算器操作
* 本计算器有输入提示符>，输入(英文输入状态下的)‘;’并换行以终止输入
* 本计算器允许连续多个“;”输入，效果与单个“;”等同
* 本计算器不允许一行多个待求表达式输入
* 本计算器允许连加连减，以及连加连减中带有乘、除、取余
* 本计算器对浮点数也可以取余(模)，计算方法为x%y=x-y*int(x/y)
* 本计算器允许一元加减运算符“-”，“+”，允许--表示两次取负得正
* 本计算器允许阶乘，但必须使用(即英文输入状态下的)半角‘!’
* 本计算器允许()、{}的使用来表示优先级
* 本计算器允许求幂次^，但是其与阶乘混用时请务必加括号()
* 本计算器使用时输入‘q’以终止程序(此功能暂时不能实现)
* 因错误退出，但希望继续使用本计算器时，请输入(英文输入状态下的)“;”以继续
* 因错误退出本计算器时，请输入“~”以关闭窗口
* 本计算器支持自定义变量，但是不支持未初始化的变量（暂未实现）
* 本计算器已经预定义了两个1变量pi和e，可直接使用
*
*
* 实现计算器功能的文法规则
* Expression：
	Term
	Expression '+' Term
	Expression '-' Term
* Term：
	Primary
	Term '*' Middle
	Term '/' Middle
	Term '%' Middle
* Middle：
	primary
	'(' Expression ')'
	'(' Expression ')'!
	'(' Expression ')'^'(' Expression ')'
	‘+’ Expression
	‘-’ Expression
* Primary：
	Number
	expression!
	expression^expression
* 
* 
* 实现变量定义功能的文法规则
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
//常量定义
const char NUMBER = 'N';
const char QUIT = 'q';
const char PRINT = ';';
const char EXIT = '~';
const string PROMPT = "> ";
const char DEFINE = '=';
const char NAME = 'a';
const char LET = 'L';
const string DECLARATION_KEY = "let";

//输入后存储类型和输入流的类型实现
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
	//获取一个Token单词
	Token get();
	//放回一个单词
	void putback(Token t);
	//清除直到字符ch的所有字符
	void cleanup_mess(char ch);

private:
	//缓存区内是否有单词
	bool isfull{ false };
	//存储放回单词的缓冲区
	Token buffer=Token(' ',0);
};
Token_Stream tokenstream;

//变量定义的类型实现
class Variable 
{
public:
	string name;
	double value;
};
vector<Variable>var_table;

//实现计算器基本文法规则的分析器函数声明
double expression();
double term();
double middle();
double primary(Token t);

//实现变量定义的函数声明
double get_value(string get_name);
void set_value(string set_name, double set_value); 
double statement();
double declaration();
bool isAlpha(char ch);
bool isDigit(char ch);
double define_name(string variable, double value);
bool is_declared(string variable);

//其他函数声明
inline void keep_your_window_open(char ch);
void error(string s);
void calculate();
void clean_up_mess();
void error_handling();

//输入后存储类型和输入流的类型的相关函数实现
void Token_Stream::putback(Token t)
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
		case PRINT:		//立即输出结果
		case QUIT:		//立即退出
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
		case '.':							//可能输入了小数
		{
			//将刚刚读入的内容放回标准输入流
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
	//首先查看缓冲区
	if (isfull&&(ch==buffer.kind))
	{
		isfull = false;
		return;
	}
	else
	{
		isfull = false;
		//查找并吸收不需要的错误流
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

//实现计算器基本文法规则的分析器函数实现
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
Middle基本表达式的文法规则：
	primary
	'(' Expression ')'
	'(' Expression ')'!
	'(' Expression ')'^'(' Expression ')'
	‘+’ Expression
	‘-’ Expression
*/
{
	//number是get_token函数可以直接读取到的内容
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
Primary基本表达式的文法规则：
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
	else if (next == '^')
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

//实现变量定义的函数实现
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
	/*设置名字set_name的变量值为set_value*/
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
			error("“=” is missing in the declaration!");
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

//其他函数实现
void error(string s)
{
	throw runtime_error(s);
}
inline void keep_your_window_open(char ch_exit)
{
	cout << "Please enter character “" << ch_exit << "” to close the window!\n";
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
		/*吃掉=符号，将t.kind变为下一个（可能为q）
		从而再次进行对q的检查，避免将q作为middle读入报错*/
		t = tokenstream.get();
	}
	if (t.kind == QUIT)
	{
		//退出
		return;
	}
	//将多读入的一个东西退回去
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
			cout << "Enter “;” to continue!\n";
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
