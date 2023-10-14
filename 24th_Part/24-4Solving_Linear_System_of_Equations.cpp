//
// Created by Zhou on 03/05/2023.
//
#include "../Head/Matrix.h"
#include "../Head/MatrixIO.h"
#include "random"
using namespace Numeric_lib;
typedef Numeric_lib::Matrix<double,2> _Matrix;
typedef Numeric_lib::Matrix<double,1> _Vector;
void classical_elimination(_Matrix &A, _Vector &b)
{
    //A为n*n阶方阵
    const Index n =A.dim1();

    //遍历第1~n-1列
    for (Index col = 0; col < n ; ++col) {
        const Index current_row = col;

        //该程序块内更换更合适的主元，以免主元为0
        {
            Index suitable_pivot_row = col;
            //查找合适的主元
            for (Index i = suitable_pivot_row + 1; i < n; ++i) {
                if (abs(A(i, col)) > abs(A(suitable_pivot_row, col)))
                    suitable_pivot_row = i;
            }
            //如果有更合适的主元，交换两行
            if (suitable_pivot_row != current_row){
                A.swap_rows(current_row, suitable_pivot_row);
                std::swap(b(current_row), b(suitable_pivot_row));
            }
        }

        //获取当前主对角线上的元素，如果为0，不存在唯一解
        const double pivot_element = A(current_row, col);
        if (pivot_element==0)
            error("There is no unique solution!");

        //初等行变换：将第col行的某倍数加至第col行 ~ 第n行
        for (Index row = current_row + 1; row < n; ++row) {
            //计算倍数
            const double multiplier = A(row, col) / pivot_element;
            //倍加
            A[row].slice(col) = scale_and_add(A[current_row].slice(col), -multiplier, A[row].slice(col));
            b(row) -= multiplier * b(current_row);
        }
    }
}
_Vector back_substitution(const _Matrix &A, const _Vector &b)
{
    //创建返回对象
    const Index n = A.dim1();
    _Vector result(n);

    //回代求解
    for (Index row = n - 1; row >= 0; --row) {
        const double col = row;

        //主元系数为0，有无穷多解，无法解出
        if (A(row, col)==0)
            error("There is no unique solution!");

        //回代
        double answer_of_x = (b(row) - dot_product(A[row].slice(col + 1), result.slice(col + 1)))/A(row, col);
        result(row) = answer_of_x;
    }
    return result;
}
_Vector classical_gaussian_elimination(_Matrix A, _Vector b)
{
    classical_elimination(A, b);
    return back_substitution(A, b);
}
_Matrix random_matrix(Index n){
    const double min=-1000,max=1000;
    _Matrix m(n,n);
    std::random_device seed;
    std::default_random_engine ran{seed()};
    std::uniform_real_distribution<> real{min,max};
    for (Index i = 0; i < n; ++i) {
        for (Index j = 0; j < n; ++j) {
            m(i,j)=real(ran);
        }
    }
    return m;
}
_Vector random_vector(Index n){
    const double min=-1000,max=1000;
    _Vector v(n);
    std::random_device seed;
    std::default_random_engine ran{seed()};
    std::uniform_real_distribution<> real{min,max};
    for (Index i = 0; i < n; ++i) {
        v(i)=real(ran);
    }
    return v;
}
_Vector operator*(const _Matrix&m, const _Vector&v){
    //系数矩阵A的行数（值等于列数）
    const Index n=m.dim1();
    _Vector result(n);
    //计算
    for (Index i = 0; i < n; ++i) {
        result(i)= dot_product(m[i],v);
    }
    return result;
}
void test_random_problem(Index n){
    //生成随机矩阵
    _Matrix A= random_matrix(n);
    _Vector b= random_vector(n);
    std::cout<<"A= "<<A<<'\n'
                <<"b= "<<b<<'\n';
    //执行测试
    try{
        _Vector x= classical_gaussian_elimination(A, b);
        std::cout<<"The solution is "<<x<<"\n\n------test result-------\n"
                    <<"Calculate A*x= "<<A*x<<'\n'
                    <<"Real value b= "<<b<<"\n------test result-------\n\n";
    } catch (std::exception&e) {
        std::cerr<<e.what()<<'\n';
    }
}
int main(){
    for (int i = 0; i < 1000; ++i) {
        std::cout<<"\nTest time: "<<i<<'\n';
        test_random_problem(3);
    }

}