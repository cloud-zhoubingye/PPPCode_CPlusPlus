//
// Created by Zhou on 2023/2/1.
//
#include "std_lib_facilities.h"

double string_to_double(string s)
{
    istringstream iss {s};
    double  num;
    iss>>num;
    if (!num)error("ERROR FORMATION OF DOUBLE NUMBER!");
    return num;
}
int main()
{
    try {
        vector<double>v;
        string s;
        cin>>s;
        for (;cin;){
            v.push_back(string_to_double(s));
            cin>>s;
            }
        for (double x:v) {
            cout << x;
        }
        return 0;
    }
    catch (runtime_error&e) {
        cerr<<"ERROR: "<<e.what();
    }
}