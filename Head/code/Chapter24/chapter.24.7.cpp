
//
// This is example code from Chapter 24.7 "Random numbers" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Matrix.h"
#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

using Numeric_lib::Index;

//------------------------------------------------------------------------------

typedef Numeric_lib::Matrix<double, 1> Vector1;

//------------------------------------------------------------------------------

Vector1 random_vector(Index n)
{
    Vector1 v(n);

    for (Index i = 0; i < n; ++i)
        v(i) = 1.0 * n * rand() / RAND_MAX;

    return v;
}

//------------------------------------------------------------------------------

int rand_int(int max) { return rand()%max; }

//------------------------------------------------------------------------------

int rand_int(int min, int max) { return rand_int(max-min)+min; }

//------------------------------------------------------------------------------

int main()
{

}

//------------------------------------------------------------------------------
