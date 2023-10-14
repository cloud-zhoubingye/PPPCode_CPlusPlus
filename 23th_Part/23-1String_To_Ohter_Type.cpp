//
// Created by Zhou on 30/04/2023.
//
#include "sstream"
#include "exception"
#include "iostream"
#include "string"
using namespace std;
struct Bad_Cast_From_String : std :: bad_cast{
    const char* what()const noexcept override{
        return "bad cast from string";
    }
};
template<typename T> T from_string(const string&s){
    istringstream is{s};
    T t;
    if (!(is>>t)) throw Bad_Cast_From_String{};
    return t;
}
template<typename Target, typename Source> Target cast_to(Source arg){
    stringstream interpreter;
    Target result;
    if (!(interpreter<<arg)||!(interpreter>>result)||!(interpreter>>std::ws).eof())
        throw runtime_error("cast to<>() failed");
    return result;
}
int main(){
    try{
        string s="99";
        int n= from_string<int>(s);
        cout<<n<<endl;
        int nn= cast_to<int>(s);
        cout<<nn<<endl;
        string s1="aaa";
        int n1= from_string<int>(s1);
        cout<<n1<<endl;
    } catch (exception &exceptions) {
        cerr<<exceptions.what()<<endl;
    }
}