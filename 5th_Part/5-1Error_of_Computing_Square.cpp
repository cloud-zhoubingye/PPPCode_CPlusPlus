#include"../Head/std_lib_facilities.h"
class bad_area{};
int area(int length, int width)
{
	if (length<=0||width<=0)
		throw bad_area{};
	return length * width;
}
int main()
{
	int length, width;
	cin >> length >> width;
	try
	{ 
		cout << area(length, width); 
	}
	catch (bad_area)
	{
		cout<<"Oops!\nThe area can't be negative!\n";
	}
}