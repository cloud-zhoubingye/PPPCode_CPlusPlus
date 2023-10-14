
//
// This is example code from Chapter 8.3 "Header Files" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

// user.cpp

#include "f.h"

//------------------------------------------------------------------------------

int g(int i)
{
    return f(i);
}

//------------------------------------------------------------------------------

int main()
{
    return g(4444);
}

//------------------------------------------------------------------------------

// f() would better be defined in its own f.cpp

int f(int n)
{
    return n;
}

//------------------------------------------------------------------------------
