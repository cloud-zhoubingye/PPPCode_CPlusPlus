#include"../Head/std_lib_facilities.h"
#include<stdlib.h>
#include<time.h>
void output(string);
void isWin(string, int);
int main()
{
	srand((unsigned)time(NULL));
	cout << "�����롰����������ʯͷ���򡰲�����\n";
	string input;
	while (cin>>input)
	{
		output(input);
		cout << "�����롰����������ʯͷ���򡰲�����\n�����롰�˳����Խ�����\n";
	}
	return 0;
}
void output(string input)
{
	//����Ӧ�����
	string output;
	int i = rand() % 3;
	switch (i)
	{
	case 0:
		output = "����";
		break;
	case 1:
		output = "ʯͷ";
		break;
	case 2:
		output = "��";
		break;
	}
	if (input == "�˳�")
	{
		exit(0);
	}
	else
	{
		cout << "�Ҹո���������ǣ�" << output << "\n";
		isWin(input, i);
	}
}
void isWin(string input,int computer_output)
{
	//�ж�˭��˭Ӯ
	int iswin{0};
	if (input == "����")
	{
		switch (computer_output)
		{
		case 0:
			iswin = 0;
			break;
		case 1:
			iswin = -1;
			break;
		case 2:
			iswin = 1;
			break;
		}
	}
	else if (input == "ʯͷ")
	{
		switch (computer_output)
		{
		case 0:
			iswin = 1;
			break;
		case 1:
			iswin = 0;
			break;
		case 2:
			iswin = -1;
			break;
		}
	}
	else if (input == "��")
	{
		switch (computer_output)
		{
		case 0:
			iswin = -1;
			break;
		case 1:
			iswin = 1;
			break;
		case 2:
			iswin = 0;
			break;
		}
	}
	else
	{
		iswin = -999;
	}
	//�����Ӯ���
	if (iswin==1)
	{
		static int win = 0;
		win++;
		cout << "��ϲ��ʤ��һ��\n��һ��ʤ����"<<win<<"��\n\n";
	}
	else if (iswin==0)
	{
		static int half = 0;
		half++;
		cout << "��ϲ�����Ҵ��ƽ��\n��һ��ƽ����" << half << "��\n\n";
	}
	else if (iswin==-1)
	{
		static int fail = 0;
		fail++;
		cout << "�޴������࣡��������\n��һ�������" << fail << "��\n\n";
	}
	else if (iswin==-999)
	{
		cout << "������Ч�����������룡\n\n";
	}
}