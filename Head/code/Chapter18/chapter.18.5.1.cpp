
//
// This is example code from Chapter 18.5.1 "Pointers to array elements" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

int main()
{
    double ad[10];
    double* p = &ad[5]; // point to ad[5]

    *p =7;
    p[2] = 6;
    p[-3] = 9;

    p += 2;             // move p two elements to the right
    p -= 5;             // move p five elements to the left
    p += 1000;          // insane: p points into an array with just 10 elements
    double d = *p;      // illegal: probably a bad value
                        //            (definitely an unpredictable value)
    *p = 12.34;         // illegal: probably scrambles some unknown data

    for (double* p = &ad[0]; p<&ad[10]; ++p) cout << *p << '\n';

    // Or backwards:

    for (double* p = &ad[9]; p>=&ad[0]; --p) cout << *p << '\n';

    double* p1 = &ad[0];
    double* p2 = p1+7;
    double* p3 = &p1[7];
    if (p2 != p3) cout << "impossible!\n";
}

//------------------------------------------------------------------------------

/*
	Expert-level comment: the "easy to get wrong" backwards loop actually has a subtle error:
	It forms a pointer to the (non-existent) element one before the array and compares that to &ad[0].
	That's not standards conforming and a very aggressive optimizer may generate bad code for that.
	However, that's unlikely because there is a lot of such code "out there".
	A correct loop:

		for (double* p = &ad[10]; p>&ad[0]; --p) cout << *(p-1) << '\n';

	However, you can't just substitute in that version in the book because then the text would be wrong.
*/

