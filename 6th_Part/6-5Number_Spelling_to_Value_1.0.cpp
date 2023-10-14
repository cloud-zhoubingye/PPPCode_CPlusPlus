#include"../Head/std_lib_facilities.h"
vector<char>num_sequence;
void input()
{
	char ch;
	while ((ch = getchar()) != '\n')
	{
		num_sequence.push_back(ch);
	}
}
int convert()
{
	int num = 0;
	for (int i = 0; i < num_sequence.size(); i++)
	{
		num += (num_sequence[i] - '0') * pow(10, (num_sequence.size()-i-1));
	}
	return num;
}
void output1()
{
	int num = convert();
	switch (num_sequence[0])
	{
	case '0':
	case '1':
		cout << "��" << num << " is "
			<< num_sequence[0] << " one��\n";
		break;
	default:
		cout << "��" << num << " is "
			<< num_sequence[0] << " ones��\n";
		break;
	}
}
void output2()
{
	int num = convert();
	if (num_sequence[0] == '1' || num_sequence[0] == '0')
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " ten and ";
	}
	else
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " tens and ";
	}
	if (num_sequence[1] == '1' || num_sequence[1] == '0')
	{
		cout << num_sequence[1] << " one��\n";
	}
	else
	{
		cout << num_sequence[1] << " ones��\n";
	}
}
void output3()
{
	int num = convert();
	if (num_sequence[0] == '1' || num_sequence[0] == '0')
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " hundred and ";
	}
	else
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " hundreds and ";
	}
	if (num_sequence[1] == '1' || num_sequence[1] == '0')
	{
		cout << num_sequence[1] << " ten and ";
	}
	else
	{
		cout << num_sequence[1] << " tens and ";
	}
	if (num_sequence[2] == '1' || num_sequence[2] == '0')
	{
		cout << num_sequence[2] << " one��\n";
	}
	else
	{
		cout << num_sequence[2] << " ones��\n";
	}
}
void output4()
{
	int num = convert();
	if (num_sequence[0] == '0' || num_sequence[0] == '1')
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " thousand and ";
	}
	else
	{
		cout << "��" << convert() << " is "
			<< num_sequence[0] << " thousands and ";
	}
	if (num_sequence[1] == '0' || num_sequence[1] == '1')
	{
		cout << num_sequence[1] << " hundred and ";
	}
	else
	{
		cout << num_sequence[1] << " hundreds and ";
	}
	if (num_sequence[2] == '0' || num_sequence[2] == '1')
	{
		cout << num_sequence[2] << " ten and ";
	}
	else
	{
		cout << num_sequence[2] << " tens and ";
	}
	if (num_sequence[3] == '0' || num_sequence[3] == '1')
	{
		cout << num_sequence[3] << " ones��\n";
	}
	else
	{
		cout << num_sequence[3] << " ones��\n";
	}
}
void output()
{
	switch (num_sequence.size())
	{
	case 1:
		output1();
		break;
	case 2:
		output2();
		break;
	case 3:
		output3();
		break;
	case 4:
		output4();
		break;
	break;
	default:
		error("Input more than four numbers");
		break;
	}
}
int main()
{
	try
	{
		input();
		output();
	}
	catch (const std::exception&e)
	{
		cout << "ERROR: " << e.what() << '\n';
	}
	return 0;
}
