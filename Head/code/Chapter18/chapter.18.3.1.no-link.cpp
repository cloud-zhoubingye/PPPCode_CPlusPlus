
//
// This is example code from Chapter 18.3.1 "Debugging constructors and destructors" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

// compile only

//------------------------------------------------------------------------------

class complex {
public:
    complex(double);    // defines double-to-complex conversion
    complex(double,double);
    // ...
};

complex z1 = 3.14;    // OK: convert 3.14 to (3.14,0)
complex z2 = complex(1.2,3.4);


//------------------------------------------------------------------------------

class vector0 {
public:
    // ...
    vector0(int);
    // ...
};

void vector0_test()
{
    vector0 v = 10; // odd: makes a vector of 10 doubles
    v = 20;         // eh? Assigns a new vector of 20 doubles to v

    void f(const vector0&);
    f(10);          // eh? calls f with a new vector of 10 doubles
}
//------------------------------------------------------------------------------

class vector {
public:
    // ...
    explicit vector(int);
    // ...
};

void vector_test()
{
    //vector v = 10;     // error: no int-to-vector conversion
    //v = 20;            // error: no int-to-vector conversion

    void f(const vector&);
    //f(10);             // error: no int-to-vector conversion
    f(vector(10));       // OK
}

//------------------------------------------------------------------------------
