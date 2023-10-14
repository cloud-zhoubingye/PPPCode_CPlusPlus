#include"../Head/std_lib_facilities.h"
int main()
{
	string previous = " ";
	string current = " ";
	int number_of_words = 0;
	//�������䣺She she laughed He He He because what he did did not look very very good good
	cout << "Please enter a sentense to find repeated place:\n"<<"    (Enter '-1' to finish this procedure)\n\n";
	while (cin>>current)
	{
		number_of_words++;
		if (previous==current)
		{
			cout << "\nWord number: " << number_of_words<<'\n'
					<< "Repeated word: " << current << "\n";
		}
		previous = current;
		if (current=="-1")
		{
			break;
		}
	} 
	return 0;
}