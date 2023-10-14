#include"../Head/std_lib_facilities.h"
int main()
{
	try
	{
		double y;
		cin >> y;
		int x = narrow_cast<int>(y);
	}
	catch (runtime_error&e)
	{
		cout << "ERROR:" << e.what() << '\n';
		keep_window_open();
		return 1;
	}
}