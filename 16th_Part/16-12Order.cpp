//
// Created by Zhou on 2023/3/23.
//
#include "../Head/std_lib_facilities.h"
#define OUTPUT_INTERVAL ','
class Purchase{
private:
    string Name;
    double Unit_Price;
    double Amount;
public:
    string name()const{return Name;}
    double unit_price()const{return Unit_Price;}
    double amount()const{return Amount;}
    string& name(){return Name;}
    double& unit_price(){return Unit_Price;}
    double& amount(){return Amount;}
    friend istream& operator>>(istream&is,Purchase&p);
    friend istream& operator>>(istream&is,vector<Purchase>&v);
    friend ostream& operator<<(ostream&os,Purchase&p);
    friend ostream& operator<<(ostream&os,vector<Purchase>&v);
};
istream& operator>>(istream &is, Purchase &p) {
    is>>p.Name>>p.Unit_Price>>p.Amount;
    return is;
}
istream &operator>>(istream &is, Vector<Purchase> &v) {
    for (Purchase p;is>>p;) v.push_back(p);
    is.clear(ios::goodbit);
    return is;
}
ostream &operator<<(ostream &os, Purchase &p) {
    os<<p.Name<<OUTPUT_INTERVAL<<p.Unit_Price<<OUTPUT_INTERVAL<<p.Amount;
    return os;
}
ostream &operator<<(ostream &os, Vector<Purchase> &v) {
    for (auto p:v) {
        os<<p<<OUTPUT_INTERVAL;
    }
    return os;
}

class Order{
private:
    string Name;
    string Address;
    vector<Purchase>Details_of_Purchase;
public:
    string& name(){return Name;}
    string name()const{return Name;}
    string& address(){return Address;}
    string address()const{return Address;}
    vector<Purchase>&details_of_purchase(){return Details_of_Purchase;}
    vector<Purchase>details_of_purchase()const{return Details_of_Purchase;}
    friend istream& operator>>(istream&is,Order&r);
    friend ostream& operator<<(ostream&os,Order&r);
};
istream &operator>>(istream &is, Order &r) {
    is>>r.Name>>r.Address>>r.Details_of_Purchase;
    return is;
}
ostream &operator<<(ostream &os, Order &r) {
    os<<r.Name<<OUTPUT_INTERVAL<<r.Address<<OUTPUT_INTERVAL<<r.Details_of_Purchase;
    return os;
}
struct Sort_By_Name{
    bool operator()(const Order&r1, const Order&r2)const{
        return r1.name()<r2.name();
    }
};
struct Sort_By_Address{
    bool operator()(const Order&r1, const Order&r2)const{
        return r1.address()<r2.address();
    }
};
void get_order(ifstream&ifs, vector<Order>&v){
    for (string line; getline(ifs,line); ) {
        stringstream ss{line};
        Order order;
        ss>>order;
        v.push_back(order);
    }
}
void write_order(ofstream&ofs, vector<Order>&v){
    ofs<<"Client_Name"<<OUTPUT_INTERVAL<<"Client_Address"<<OUTPUT_INTERVAL<<"Goods_Name"
    <<OUTPUT_INTERVAL<<"Goods_UnitPrice"<<OUTPUT_INTERVAL<<"Goods_Amount"<<endl;
    for (auto p:v) {
        ofs<<p<<endl;
    }
}
double total_money(const vector<Order>&v){
    double money=0;
    for (auto p:v) {
        for (auto q:p.details_of_purchase()) {
            money+=q.amount()*q.unit_price();
        }
    }
    return money;
}
int main(){
    try {
        vector<Order>v;
        ifstream ifs{R"(D:\MyProgramme\C++_Programming\C++Principles_and_Practise\My_Test_txt\16-12Shop_Order.txt)"};
        if(ifs) get_order(ifs,v);
        else throw runtime_error("Open Read_File Error !\n");
        ifs.close();
        ofstream ofs{R"(D:\MyProgramme\C++_Programming\C++Principles_and_Practise\My_Test_txt\16-12Shop_Order.csv)",ios_base::out};
        sort(v.begin(),v.end(),Sort_By_Name());
        if(ofs) write_order(ofs,v);
        else throw runtime_error("Open Write_File Error !\n");
        ofs.close();
        ofstream ofs1{R"(D:\MyProgramme\C++_Programming\C++Principles_and_Practise\My_Test_txt\16-12Shop_Order.csv)",ios_base::app};
        sort(v.begin(),v.end(),Sort_By_Address());
        if(ofs1) write_order(ofs1,v);
        else throw runtime_error("Open Write_File Error !\n");
        ofs1.close();
        cout<<"Total Turnover: $"<<total_money(v)<<endl;
    } catch (runtime_error&r) {
        cerr<<r.what();
    }
}