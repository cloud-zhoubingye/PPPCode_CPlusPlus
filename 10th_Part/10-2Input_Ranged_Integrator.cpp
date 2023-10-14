#include"../Head/input_restricted_int.h"
namespace input_restricted_int
{
	const string NOT_NUMBER_ERROR = "Sorry ! That is not a number !\nPlease try again !\n";
	const string EOF_ERROR = "Using EOF as an input is illegal !";
	void skip_to_int()
	{
		if (cin.fail())
		{
			cin.clear(ios_base::goodbit);
			cerr << NOT_NUMBER_ERROR;
			for (char ch; cin >> ch; )
			{
				if (isdigit(ch))
				{
					cin.unget();
					return;
				}
			}
			throw runtime_error(EOF_ERROR);
		}
	}
	int get_int()
	{
		int input = 0;
		while (true)
		{
			if (cin >> input) return input;
			else skip_to_int();
		}
	}
	int get_special_int(int low, int high, bool& is_inputed)
	{
		cout << "Please enter an integer in the range [" << low << ',' << high << "] :" << endl;
		while (true)
		{
			int input = get_int();
			if (input >= low && input <= high)
			{
				is_inputed = true;
				return input;
			}
			else
				cerr << "Sorry! " << input << " is not in the [" << low << ',' << high << "] range !\nPlease try again!\n";
		}
	}
}
int get_restricted_int(int low, int high)
{
	int input_restricted_int_input = 0;
	bool is_input_restricted_int_inputed = false;
	for (;;)
	{
		try
		{
			input_restricted_int_input = input_restricted_int::get_special_int(20, 300, is_input_restricted_int_inputed);
		}
		catch (const std::exception& input_restricted_int_e)
		{
			cerr << "ERROR:\n" << input_restricted_int_e.what();
		}
		if (is_input_restricted_int_inputed)
		{
			break;
		}
	}
	return input_restricted_int_input;
}