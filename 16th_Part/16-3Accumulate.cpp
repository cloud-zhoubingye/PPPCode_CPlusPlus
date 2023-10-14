//
// Created by Zhou on 2023/3/16.
//
#include "iostream"
#include "functional"
#include "vector"
#include "string"
#include "numeric"
struct Goods{
    std::string name;
    int materials_expense;
    int packing_expense;
    double bonus_rate;
};
template<typename Iterator,typename T,typename BinOp>
//要求Input_iterator<Iterator>()和Number<T>()和Binary_operator<BinOp,Value_type<Iterator>,T>()
T Accumulate(Iterator first, Iterator last, T init, BinOp op){
    while (first!=last){
        init =op(*first,init);
        ++first;
    }
    return init;
}
struct price{
    double operator()(double init,const Goods&g){return init+g.materials_expense+g.packing_expense*g.bonus_rate;}
};
int main(){
    int a[]={1,2,3,4};
    std::cout << Accumulate(a, a + 4, 1, std::multiplies<double>()) << std::endl;

    std::vector<Goods>v={Goods{"A",100,100,0.8},\
    Goods{"B",100,100,0.8},\
    Goods{"C",100,100,0.8},\
    Goods{"D",100,100,0.8}
    };
    std::cout<<accumulate(v.begin(),v.end(),0.0, price());
}