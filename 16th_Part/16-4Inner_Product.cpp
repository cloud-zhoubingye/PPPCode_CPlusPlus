//
// Created by Zhou on 2023/3/17.
//
#include "iostream"
#include "list"
#include "numeric"
#include "functional"
#include "vector"
template<typename Iterator1,typename Iterator2,typename T>
T Inner_product(Iterator1 first,Iterator1 last,Iterator2 another_first,T init){
    while(first!=last){
        init+=(*first)*(*another_first);
        ++first;
        ++another_first;
    }
    return init;
}
template<typename Iterator1,typename Iterator2,typename T,typename BinOp1,typename BinOp2>
T Inner_product(Iterator1 first,Iterator1 last,Iterator2 another_first,T init,BinOp1 op1,BinOp2 op2){
    while (first!=last){
        init=op1(init,op2((*first),(*another_first)));
        ++first;
        ++another_first;
    }
    return init;
}
int main(){
    std::vector<double>price={81.86,34.69,54.45};
    std::list<double>weight={5.8549,2.4808,3.8940};
    double index= Inner_product(price.begin(),price.end(),weight.begin(),0.0);
    std::cout<<"该公司综合估值为："<<index<<std::endl;
    double index1= Inner_product(price.begin(),price.end(),weight.begin(),0.0,std::plus<double>(),std::multiplies<double>());
    std::cout<<"该公司综合估值为："<<index1<<std::endl;
    double index2= std::inner_product(price.begin(),price.end(),weight.begin(),0.0,std::plus<double>(),std::multiplies<double>());
    std::cout<<"该公司综合估值为："<<index2<<std::endl;
}