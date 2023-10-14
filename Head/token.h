#pragma once
#include"std_lib_facilities.h"
class Token
{
public:
	char kind;
	double value = 0;
};
class Token_Stream
{
public:
	//��ȡһ��Token���ʣ��۲����ƣ�
	Token get()
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
			if (!cin)
			{
				error("Bad input!");
			}
			//���ոն�������ݷŻر�׼������
			cin.putback(ch);
			double value;
			cin >> value;
			if (!cin)
			{
				error("Bad input!");
			}
			Token t = { ch,value };
			return t;
		}
	}
	//�Ż�һ������
	void putback(Token t)
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
	//���ֱ���ַ�ch�������ַ�
	void cleanup_mess(char ch)
	{
		//���Ȳ鿴������
		if (isfull && (ch == buffer.kind))
		{
			isfull = false;
			return;
		}
		else
		{
			isfull = false;
			//���Ҳ����ղ���Ҫ�Ĵ�����
			char ch_rubbish;
			while (cin >> ch_rubbish)
			{
				if (ch_rubbish == ch)
				{
					return;
				}
			}
		}
	}

private:
	//���������Ƿ��е���
	bool isfull{ false };
	//�洢�Żص��ʵĻ�����
	Token buffer;
};