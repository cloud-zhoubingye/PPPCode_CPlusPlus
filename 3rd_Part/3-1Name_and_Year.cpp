#include"../Head/std_lib_facilities.h"
int main()
{
	string first_name = "???";			// ???��ʾ��֪������
	string second_name = "???";
	int age = -1;								// -1��ʾ��֪������
	cout << "Please enter your first name, second name and age:\n";
	cin >> first_name>>second_name>> age;
	cout << "Hello,"<<first_name<<second_name<<"(age " << age << ")";
	return 0;
}