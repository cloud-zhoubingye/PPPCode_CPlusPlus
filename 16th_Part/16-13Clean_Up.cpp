//
// Created by Zhou on 2023/3/23.
//
#include "../Head/std_lib_facilities.h"
class Words{
public:
    using line=string;
    vector<line>&words(){return v;}
    vector<line>words()const{return v;}
    void replace();
    void get(istream&is);
    void put(ostream&os);
    strong_ordering operator<=>(const Words&) const=default;
    bool operator==(const Words&)const=default;

private:
    void replace_ch();
    void decline_plural();
    vector<line>v;
};
void Words::replace_ch() {
    for (line& s : v) {
        for (char& ch : s) {
            if (!(isdigit(ch)||isalpha(ch))) ch=' ';
            if (isalpha(ch)) ch= tolower(ch);
        }
    }
}
void Words::decline_plural() {
    for (line& s : v) {
        for (int i = 0; i < s.size(); ++i)
            if (i==s.size()-2&&s[i]=='e'&&s[i+1]=='s'){
                s[i]=' ';
                s[i+1]=' ';
            }
            else if ((i<=s.size()-1&&s[i]=='s')||(s[i]=='s'&&s[i+1]==' '))
                s[i]=' ';
    }
}
void Words::replace() {
    replace_ch();
    decline_plural();
}
void Words::get(istream &is) {
    for (string s;is>>s;) v.push_back(s);
    is.clear(ios::goodbit);
}
void Words::put(ostream &os) {
    for (string s:v)
        os<<s<<endl;
}

int main(){
    Words w;
    w.get(cin);
    w.replace();
    w.put(cout);
}