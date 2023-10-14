//
// Created by Zhou on 2023/3/19.
//
#include <algorithm>
#include "numeric"
#include "iomanip"
#include "iostream"
#include "unordered_map"

using namespace std;
//道琼斯工业指数
int main() {
    //由股票代码映射到股价
    unordered_map<string,double>dow_price={
            {"MMM",81.86},
            {"AA",34.69},
            {"MO",54.45}
    };
    //由股票代码映射到权重
    unordered_map<string,double>dow_weight={
            {"MMM",5.8549},
            {"AA",2.4808},
            {"MO",3.8940}
    };
    //由股票代码映射到全名
    unordered_map<string,string>dow_name={
            {"MMM","3M Co."},
            {"AA","Alcoa Inc."},
            {"MO","Altria Group Inc."}
    };
    //输出
    for (const auto& p : dow_price) {
        cout<<p.first<<'\t'
        <<p.second<<'\t'
        <<dow_name[p.first]<<endl;
    }
    //计算工业指数
    double dji_index= inner_product(dow_price.begin(),dow_price.end(),dow_weight.begin(),0.0,plus<double>(), [](const pair<string,double>&a,const pair<string,double>&b){return a.second*b.second;});
    //输出
    cout<<fixed<<setprecision(6)<<"Index: "<<dji_index<<endl;
}