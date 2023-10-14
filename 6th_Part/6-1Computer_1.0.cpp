/*****************************************************************************************************************************************
* 
* ������1.0�汾
* 
* ������������һ�����ж�ν��м���������
* ������������������롮=������ֹ����
* ���������������������������������������д��г˳�
* 
*****************************************************************************************************************************************/


#include"../Head/std_lib_facilities.h"
#include<cctype>
string ToLower(string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}
bool is_Go_on()
{
	string isgo_on;
	cout << "����continue�Լ���ʹ�ü�����,�����������������Խ�����" << endl;
	cin >> isgo_on;
	isgo_on = ToLower(isgo_on);
	if (isgo_on=="continue")
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Error(string s)
{
	throw runtime_error(s);
}
void calculate(int *left_val, const char operater, int* right_val)
{
	switch (operater)
	{
	case '+':
		*right_val += *left_val;
		break;
	case'-':
		*right_val = *left_val - *right_val;
		break;
	case'*':
		*right_val *= *left_val;
		break;
	case'/':
		*right_val = *left_val/(*right_val);
		break;
	default:
		Error("Wrong operator!");
		break;
	}
	*left_val = *right_val;
}
void input_left(int* left_val)
{
	cout << "Please enter expression (We can handle +,-,*,/)" << endl
		<< "add an ��=�� to end expression��(e.g. 1+5=)" << endl;
	cin >> *left_val;
	if (!cin)
	{
		//��ֹ�û�����������
		Error("No fisrt operand!");
	}
}
int input_right(char* operater, int* right_val)
{
	cin >> *operater;
	if (*operater == '=')
	{
		//�û�ϣ����������
		return -1;
	}
	cin >> *right_val;
	if (!cin)
	{
		//��ֹ�û�����������
		Error("No second operand!");
	}
	return 0;
}
int main()
{
	try
	{
		int left_val = 0;
		int right_val = 0;
		char operater = ' ';
		int result = 0;
here:
		//����
		input_left(&left_val);
		for (;;)
		{
			int isOver = input_right(&operater, &right_val);
			if (isOver==0)
			{
				//�ɹ�����
				//���м���
				calculate(&left_val, operater, &right_val);
			}
			else if (isOver==-1)
			{
				//�û���������
				cout << left_val << endl;
				//�Ƿ����
				if (is_Go_on())
				{
					goto here;
				}
				break;
			}
		}
	}
	catch (const std::exception&e)
	{
		cerr << e.what()<<endl;
		cin.clear();
		cin.sync();
		keep_window_open();
	}
	return 0;
}