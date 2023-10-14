#include"../Head/std_lib_facilities.h"
#include<stdlib.h>

//����һ������
class Name_Score
{
public:
	string name;
	double score;
private:
};
vector<Name_Score>name_score;

//��������
Name_Score according_name(string name);
void according_score(double score);
void input();
bool isrepetited(string name);
void mode_control();

//��������
Name_Score according_name(string name)
{
	for (int i = 0; i < name_score.size(); i++)
	{
		if (name_score[i].name == name)
		{
			return name_score[i];
		}
	}
	error("SORRY!NAME NOT FOUND!");
}
void according_score(double score)
{
	bool isfound = false;
	for (int i = 0; i < name_score.size(); i++)
	{
		if (name_score[i].score == score)
		{
			isfound = true;
			cout << name_score[i].name << '\t' << name_score[i].score << '\n';
		}
	}
	if (!isfound)
	{
		error("SORRY! SCORE NOT FOUND!");
	}
}
void input()
{
	string name;
	double score;
	Name_Score this_name_score;
	cout << "������ѧ�������ͳɼ�(�ո����)��\n����CTRL+Z�Խ���\n";
	while (cin >> name)
	{
		if (isrepetited(name))
		{
			error("NAME REPETITED!");
		}
		else
		{
			cin >> score;
			if (!cin)
			{
				error("WRONG SCORE!");
			}
			else
			{
				this_name_score = { name,score };
				name_score.push_back(this_name_score);
			}
		}
	}
	if (!cin)
	{
		string isover = "";
		cin >> isover;
		if (isover=="")
		{

		}
		else
		{
			error("WRONG NAME!");
		}
	}
}
bool isrepetited(string name)
{
	bool isRepetited = false;
	for (size_t i = 0; i < name_score.size(); i++)
	{
		if (name_score[i].name == name)
		{
			isRepetited = true;
			break;
		}
	}
	return isRepetited;
}
void mode_control()
{
	string name;
	double score;
	for (;;)
	{
		int mode_control = 0;
		cout << "����������1��ͨ��������ѯѧ���ɼ���Ҳ��������2��ͨ���ɼ�����ѧ����������������-1�Խ�����\n";
		cin.clear();
		cin.sync();
		cin>> mode_control;
		if (mode_control == 1)
		{
			cout << "������ѧ��������\n";
			cin >> name;
			Name_Score this_one;
			this_one = according_name(name);
			cout << this_one.name << '\t' << this_one.score << '\n';
		}
		else if (mode_control == 2)
		{
			cout << "������ѧ���ɼ���\n";
			cin >> score;
			Name_Score this_one;
			according_score(score);
		}
		else if (mode_control == -1)
		{
			cout << "���˳���\n";
			exit(0);
		}
		else
		{
			error("������Ч��");
		}
	}
}
int main()
{
	try
	{
		input();
		cout << "�������!\n";
		mode_control();
	}
	catch (const std::exception&err)
	{
		cout << "ERROR: " << err.what() << "\n";
	}
}