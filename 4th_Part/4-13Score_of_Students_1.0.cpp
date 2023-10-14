#include"../Head/std_lib_facilities.h"
bool isrepetited(vector<string>name, string Name)
{
	bool isRepetited = false;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i] == Name)
		{
			isRepetited = true;
			break;
		}
	}
	return isRepetited;
}
void according_name(vector<string>name, vector<int>score, string Name)
{
	bool isfound = false;
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i]==Name)
		{
			isfound = true;
			cout << name[i] << ": " << score[i] <<"��" << '\n';
			break;
		}
	}
	if (!isfound)
	{
		cout << "Sorry!\tNOT FOUND!\n";
	}
}
void according_score(vector<string>name, vector<int>score, int Score)
{
	bool isfound = false;
	for (int i = 0; i < score.size(); i++)
	{
		if (score[i]==Score)
		{
			isfound = true;
			cout << name[i] << ": " << score[i] << "��" << '\n';
		}
	}
	if (!isfound)
	{
		cout << "Sorry!\tNOT FOUND!\n";
	}
}
int main()
{
	//��������
	cout << "������ѧ�������ͳɼ�(�ո����)��\n���롰NO MORE���Խ���\n";
	vector<int>score;
	vector<string>name;
	int Score;
	string Name;
	while (cin>>Name>>Score)
	{
		if (isrepetited(name,Name))
		{
			cout << "ERROR����������������ظ���\n";
			return 0;
		}
		else
		{
			name.push_back(Name);
			score.push_back(Score);
		}
	}
	//���
	cout << "�������!\n";
	for (;;)
	{
		int mode_control = 0;
		cout << "����������1��ͨ��������ѯѧ���ɼ���Ҳ��������2��ͨ���ɼ�����ѧ����������������-1�Խ�����\n";
		cin.clear();
		cin.sync();
		cin >> mode_control;
		if (mode_control == 1)
		{
			cout << "������ѧ��������\n";
			cin.clear();
			cin.sync();
			cin >> Name;
			according_name(name,score,Name);
		}
		else if (mode_control == 2)
		{
			cout << "������ѧ���ɼ���\n";
			cin.clear();
			cin.sync();
			cin >> Score;
			according_score(name,score,Score);
		}
		else if (mode_control==-1)
		{
			return 0;
		}
		else
		{
			cout << "ERROR��������Ч��\n�����ԣ�\n\n";
		}
	}
}
