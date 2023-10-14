
//
// This is example code from Chapter 9.6 "Operator overloading" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------

enum Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

//------------------------------------------------------------------------------

Month operator++(Month& m)                       // prefix increment operator
{
    m = (m==Dec) ? Jan : Month(m+1);             // "wrap around"
    return m;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, Month m)
{
    static const char* month_tbl[12] = {
        "January","February","March","April","May","June","July",
        "August","September","October","November","December"
    };
    return os << month_tbl[m-1];
}

//------------------------------------------------------------------------------

class Vector {};

//int operator+(int,int);        // error: you can't overload built-in +
Vector operator+(const Vector&, const Vector &); // ok 
Vector operator+=(const Vector&, int);           // ok

//------------------------------------------------------------------------------

int main()
{
    Month m = Sep;
    ++m;                // m becomes Oct
    ++m;                // m becomes Nov
    ++m;                // m becomes Dec
    ++m;                // m becomes Jan ("wrap around")
    cout << m << endl;
    return 0;
}

//------------------------------------------------------------------------------
