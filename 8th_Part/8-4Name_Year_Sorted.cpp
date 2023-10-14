#include"../Head/vector_quick_operator.h"
#include"../Head/std_lib_facilities.h"
//�ѵ�������2��vector��name������任��age��vectorû�䣬��ζ�Ӧ��
//�ѵ�������1��vector���������ף�������鷳
vector<string>Name;
vector<string>Name_copy;
vector<int>Age;
vector<int>Age_sorted;
void my_input()
{
	cout << "����������������\n";
	string name;
	int age;
	while (cin >> name >> age)
	{
		Name.push_back(name);
		Age.push_back(age);
	}
}
void copy_it()
{
	for (string x : Name)
	{
		Name_copy.push_back(x);
	}
}
void sort_it()
{
	sort(Name);
	for (size_t i = 0; i < Name.size(); i++)
	{
		for (size_t j = 0; j < Name_copy.size(); j++)
		{
			if (Name[i] == Name_copy[j])
			{
				Age_sorted.push_back(Age[j]);
				break;
			}
		}
	}
}
int main()
{
	my_input();
	copy_it();
	sort_it();
	print_vector_string(Name);
	print_vector_int(Age_sorted);
	return 0;
}


