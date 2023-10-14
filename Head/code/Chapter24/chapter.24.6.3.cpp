
//
// This is example code from Chapter 24.6.3 "Testing" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Matrix.h"
#include "MatrixIO.h"
#include "../std_lib_facilities.h"

using Numeric_lib::Index;

//------------------------------------------------------------------------------

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector1;

//------------------------------------------------------------------------------

void classical_elimination(Matrix& A, Vector1& b);

//------------------------------------------------------------------------------

Vector1 back_substitution(const Matrix& A, const Vector1& b);

//------------------------------------------------------------------------------

// An exception of this type is thrown when elimination fails.
struct Elim_failure : std::domain_error {
    Elim_failure(string s) : std::domain_error(s) { }
};

//------------------------------------------------------------------------------

// An exception of this type is thrown when back substitution fails.
struct Back_subst_failure : std::domain_error {
    Back_subst_failure(string s) : std::domain_error(s) { }
};

//------------------------------------------------------------------------------

Vector1 classical_gaussian_elimination(Matrix A, Vector1 b)
{
    classical_elimination(A, b);
    return back_substitution(A, b);
}

//------------------------------------------------------------------------------

void classical_elimination(Matrix& A, Vector1& b)
{
    const Index n = A.dim1();

    // traverse from 1st column to the next-to-last
    // filling zeros into all elements under the diagonal:
    for (Index j = 0; j<n-1; ++j) {
        const double pivot = A(j,j);
        if (pivot == 0) throw Elim_failure("Elimination failure in row " + to_string(j));

        // fill zeros into each element under the diagonal of the ith row:
        for (Index i = j+1; i<n; ++i) {
            const double mult = A(i,j)/pivot; 
            A[i].slice(j) = scale_and_add(A[j].slice(j),-mult,A[i].slice(j));
            b(i) -= mult*b(j); // make the corresponding change to b
        }
    }
}

//------------------------------------------------------------------------------

Vector1 back_substitution(const Matrix& A, const Vector1& b)
{
    const Index n = A.dim1();
    Vector1 x(n);

    for (Index i = n-1; i>=0; --i) {
        double s = b(i)-dot_product(A[i].slice(i+1),x.slice(i+1));

        if (double m = A(i,i))
            x(i) = s/m;
        else
            throw Back_subst_failure("Back substitution failure in row " + to_string(i));
    }

    return x;
}

//------------------------------------------------------------------------------

Vector1 random_Vector1(Index n)
{
    Vector1 v(n);

    for (Index i = 0; i < n; ++i)
        v(i) = 1.0 * n * rand() / RAND_MAX;

    return v;
}

//------------------------------------------------------------------------------

Matrix random_matrix(Index n)
{
    Matrix m(n,n);

    for (Index i = 0; i < n; ++i)
        m[i] = random_Vector1(n);

    return m;
}

//------------------------------------------------------------------------------

Vector1 operator*(const Matrix& m, const Vector1& u)
{
    const Index n = m.dim1();
    Vector1 v(n);
    for (Index i = 0; i < n; ++i) v(i) = dot_product(m[i], u);
    return v;
}

//------------------------------------------------------------------------------

void solve_random_system(Index n)
{
    Matrix A = random_matrix(n);    // see §24.6
    Vector1 b = random_Vector1(n);

    cout << "A = " << A << endl;
    cout << "b = " << b << endl;

    try {
        Vector1 x = classical_gaussian_elimination(A, b);
        cout << "classical elim solution is x = " << x << endl;
        Vector1 v = A * x;
        cout << " A * x = " << v << endl;
    }
    catch(const exception& e) {
        cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------

int main()
{
    solve_random_system(3);
    solve_random_system(4);
    solve_random_system(5);
}

//------------------------------------------------------------------------------

