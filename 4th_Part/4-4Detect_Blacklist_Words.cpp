#include"../Head/std_lib_facilities.h"

vector<string> Eliminating_Redundancy(vector<string> dislike);
bool isRepetition(string word, vector<string>dislike);
vector<string> input(vector<string> dislike);

int main()
{
	//�����������ʿ�
	vector<string> dislike;
	cout << "������������е�Ӣ�ĵ���(�ո����,CTRL+Z����)��\n";
	string bad_words;
	while (cin >> bad_words)
	{
		dislike.push_back(bad_words);
	}
	//�������ʿ�ȥ��
	dislike=Eliminating_Redundancy(dislike);
	//�����ı�
	vector<string> text=input(dislike);
	//���
	for (string x : text)
	{
		cout << x << ' ';
	}
	cout << '\n';
	return 0;
}

vector<string> Eliminating_Redundancy(vector<string> dislike)
{
	vector<string> new_dislike;
	string x;
	sort(dislike);
	for (size_t i = 0; i < dislike.size(); i++)
	{
		if (i==dislike.size()-1||dislike[i]!=dislike[i+1])
		{
			x=dislike[i];
			new_dislike.push_back(x);
		}
	}
	return new_dislike;
}

bool isRepetition(string word, vector<string>dislike)
{
	bool isSame = false;
	for (string x : dislike)
	{
		if (x==word)
		{
			isSame = true;
			break;
		}
	}
	return isSame;
}

vector<string> input(vector<string> dislike)
{
	vector<string> Text;
	cout << "�������ı������������ĸ�Ϳո���Ķ�������-1����\n";
	fflush(stdin);
	string words;
	cin.clear();
	cin.sync();
	cin >> words;
	while (words != "-1")
	{
		if (isRepetition(words, dislike))
		{
			Text.push_back("BLACK_LIST");
		}
		else
		{
			Text.push_back(words);
		}
		cin.clear();
		cin.sync();
		cin >> words;
	}
	return Text;
}