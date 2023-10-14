
//
// This is example code from Chapter 25.5.3 "Signed and unsigned" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>
#include <vector>
#include<string>

using namespace std;

namespace LLL {
	typedef short UInt16;
	
template<class T =UInt16>
struct selection_base : public std::vector<T> {
	// ...
	bool operator()(UInt16) { return true; }; // contains index?
	// ...
};

template<class T, class S>
void f(
std::vector<T>& set,
S& sel,
UInt16 index
)
{
	if(sel(index)) {
		// ...
	}
}

void g(int,selection_base<int>& s)
{
		vector<int> v;
	f(v,s,7);
}

} // LLL


namespace DDD {
	struct Date {
		Date(const char*) {}
		explicit Date(long) {}
	};

	int f(Date) { return 0; }

	Date d1 = "xxx";
	int d2 = f("mmm");

//	Date d3 = 22;
//	int d3 = f(33);

	template<int N> int fac() { return N*fac<N-1>(); }
	
	template<> int fac<1>() { return 1; }

	int x = fac<7>();
}

//------------------------------------------------------------------------------

void infinite()
{
    unsigned char max = 160;    // very large
    for (signed char i=0; i<max; ++i) cout << int(i) << endl;
}

//------------------------------------------------------------------------------

template<class T> void print(T i) { cout << i << '\t'; }

//------------------------------------------------------------------------------

void print(char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

void print(signed char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

void print(unsigned char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

char* ident(char * p) { return p; }

char& r = *ident(0);	// invalid code
//------------------------------------------------------------------------------

//int xxx;
//int& aaa[] = { xxx };
//------------------------------------------------------------------------------

struct Address {
	char* name;		// "Jim Dandy"
	int number;		// 61
	char* street;		// "South St"
	char* town;		// "New Providence"
	char state[2];		// 'N' 'J'
	char* zip;			// "07974"
};

void addr()
{
		cout << "sizeof(Address) " << sizeof(Address) << "\n";
}

//------------------------------------------------------------------------------

#define printx(x) cout << #x << " = " << x << '\n';

int a = 7;
string s = "asdf";

void fhack()
{
	printx(a);
	printx(s);
}

//------------------------------------------------------------------------------


template <typename T>
int foo(T x) {
    return T::bar;
}

struct SS { static int bar; };

int SS::bar;

int ttt()
{
	SS s;
	return foo(s);
}

//------------------------------------------------------------------------------

char a1[] = { 1,2,3,4 };
//char* p = { '1','2','3','4' };
//char (&a2)[] ; //= { 1,2,3,4};
char (&a3)[4] = a1; // = { 1,2,3,4};

void f1(char*){};
void f2(char[]){}
void f3(char[4]);
//void f4(char(&a)[]);
void f5(char(&a)[4]);

void ff()
{
	f1("asdf");
	f2("asdf");
}

typedef int int_arr_t[];
int a4[]= {1, 2, 3, 4};
int_arr_t a5 = {1, 2, 3, 4};

/*
struct X {
	int i;
	X(int) { }
//	X(const X&) { }
};

X a;
X b ( 1 );
*/
auto d1 = 2.1;
/*
int main(int argc, char* argv[])
{
	cout << "main(" << argc << ' ' << argv[0] << ")\n";
	fhack();
		addr();
		int zz = ttt();

	cout << d1 << '\n';
	char cc ; cin >> cc;

    vector<int> v;
    // ...
    for (int i = 0; i<v.size(); ++i) cout << i << endl;
    
    for (vector<int>::size_type i = 0; i<v.size(); ++i) cout << i << endl;
    
    for (vector<int>::iterator p = v.begin(); p!=v.end(); ++p) cout << p-v.begin() << endl;

    // ...

    {
        unsigned int ui = -1;
        int si = ui;
        int si2 = ui+2;
        unsigned ui2 = ui+2;
    }

    // What happens if an integer overflows? Consider:

    short int i = 0;
   while (++i) print(i); // print i as an integers followed by a space

    int si = 257;         // doesn't fit into a char
    char c = si;          // implicit conversion to char
    unsigned char uc = si;
    signed char sc = si;
    print(si); print(c); print(uc); print(sc); cout << endl;

    si = 129;             // doesn't fit into a signed char
    c = si;
    uc = si;
    sc = si;
    print(si); print(c); print(uc); print(sc);

}
*/
//------------------------------------------------------------------------------
