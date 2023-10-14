
//
// This is example code from Chapter 11.2.2 "Integer input" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

int main()
{
    int a;
    int b;
    int c;
    int d;
    cin >> a >> hex >> b >> oct >>  c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

    cin.unsetf(ios::dec);    // don't assume decimal (so that 0x can mean hex)
    cin.unsetf(ios::oct);    // don't assume octal (so that 12 can mean twelve)
    cin.unsetf(ios::hex);    // don't assume hexadecimal (so that 12 can mean twelve)

    cin >>a >> b >> c >> d;
}

//------------------------------------------------------------------------------
