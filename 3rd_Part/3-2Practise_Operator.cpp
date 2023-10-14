#include"../Head/std_lib_facilities.h"
int main()
{
	//��ϰ���������
	cout << "��ϰ���������\nPlease enter a floating-point value:\n";
	double n;
	cin >> n;
	cout << "n=" << n << "\n"
			<< "n+1=" << n + 1 << "\n"
			<< "three times n=" << 3 * n << '\n'
			<< "n squared=" << pow(n, 2) << '\n'
			<< "n squared root=" << sqrt(n) << "\n"
			<< "half of n=" << n / 2 << "\n";
	//��ȡ�պ���
	cout << "\n��ȡ�պ���\nPlease enter your first and second names\n";
	string first = "???", second = "???";
	cin >> first >> second;
	string name = first + ' ' + second;
	cout << "Hello," << name << "\n";
	//���벢�Ƚ���������
	cout << "\n���벢�Ƚ���������\nPlease enter two people's first name and second name:\n";
	string people1_firstname = "???", people1_secondname = "???";
	string people2_firstname = "???", people2_secondname = "???";
	cin >> people1_firstname >> people1_secondname;
	cin >> people2_firstname >> people2_secondname;
	string people1_name = people1_firstname + ' ' + people1_secondname;
	string people2_name = people2_firstname + ' ' + people2_secondname;
	if (people1_name==people2_name)
		cout << "That's the same name\n";
	else if (people1_name < people2_name)
		cout << people2_name << " is alphabetically after " << people1_name << '\n';
	else
		cout << people1_name << " is alphabetically after " << people2_name << '\n';
	return 0;
}
