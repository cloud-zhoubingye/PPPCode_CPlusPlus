#include"../Head/std_lib_facilities.h"

class Name_Pairs
{
public:
	//����һ�������б�
	void read_name();
	//�����б���ÿ�����ֵ�����
	void read_age();
	//name�������ֵ�������
	void sort_according_name();
	//��ȡ���ݺ���
	vector<string>name() { return Name; }
	vector<int>age() { return Age; }

private:
	vector<string> Name;
	vector<int> Age;
};
void Name_Pairs::read_name()
{
	cout << "������һ�������б�\n";
	string input;
	while (cin>>input)
	{
		Name.push_back(input);
	}
}
void Name_Pairs::read_age()
{
	cout << "��Ϊ����ÿһ���û���������\n";
	for (size_t i = 0; i < Name.size(); i++)
	{
			int input;
			cout << Name[i] << ": \n";
			cin.clear();
			cin.sync();
			cin >> input;
			Age.push_back(input);
	}
}
void Name_Pairs::sort_according_name()
{
	vector<string> name_copy;
	name_copy = Name;
	sort(Name);
	vector<int>age_sorted;
	for (string s : Name)
	{
		for (size_t i = 0; i < name_copy.size(); i++)
		{
			if (s==name_copy[i])
			{
				age_sorted.push_back(Age[i]);
				break;
			}
		}
	}
	Age = age_sorted;
}

ostream& operator<<(ostream& os, Name_Pairs name_pairs)
{
	for (size_t i = 0; i < name_pairs.name().size(); i++)
	{
		os << name_pairs.name()[i] << ": " << name_pairs.age()[i] << '\n';
	}
	return os;
}
bool operator==(Name_Pairs N1, Name_Pairs N2)
{
	if (N1.age()==N2.age())
	{
		if (N1.name()==N2.name())
		{
			return true;
		}
	}
	return false;
}
bool operator!=(Name_Pairs N1, Name_Pairs N2)
{
	if (N1.age() == N2.age())
	{
		if (N1.name() == N2.name())
		{
			return false;
		}
	}
	return true;
}

int main()
{
	Name_Pairs t;
	t.read_name();
	t.read_age();
	cout << t;
	t.sort_according_name();
	cout << t;
}