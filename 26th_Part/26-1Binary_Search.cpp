//
// Created by Zhou on 04/05/2023.
//
#include "chrono"
#include "../Head/std_lib_facilities.h"
template<typename ForwardIterator, typename T>
bool binary_searching(ForwardIterator first, ForwardIterator last, const T& value){
    return binary_search(first,last,value);
}

struct Test{
        string label;
        int val;
        vector<int>seq;
        bool res;
};
istream & operator>>(istream&is,Test&t){
    char ch;
    is>>ch>>t.label>>t.val>>ch;
    vector<int>seq;
    for (;is>>ch;) {
        if (ch=='}') break;
        is.putback(ch);
        int num;
        is>>num;
        seq.push_back(num);
    }
    t.seq=seq;
    is>>t.res>>ch;
    return is;
}
int test_all(istream&is){
    int err_cnt=0;
    for(Test t;is>>t;){
        bool r= binary_searching(t.seq.begin(),t.seq.end(),t.val);
        if (r!= t.res){
            cerr<<"Failure: test "<<t.label
            <<"\n\tbinary_search: "<<t.seq.size()
            <<" \telements, val=="<<t.val
            <<"\n\tactually ->"<<!t.res
            <<" \texpected->"<<t.res<<endl;
            ++err_cnt;
        }
    }
    return err_cnt;
}
void make_test(ofstream &ofs, const string&lab, int n, int least_number, int max_spread){
    vector<int>v;
    int element=least_number;
    for (int i = 0; i < n; ++i) {
        element+= randint(max_spread);
        v.push_back(element);
    }
    int val=least_number+ randint(element-least_number);
    ofs<<"{ "<<lab<<' '<<val<<" { ";
    bool found= false;
    for (int i = 0; i < n; ++i) {
        if (v[i]==val) found= true;
        ofs<<v[i]<<' ';
    }
    ofs<<"} "<<found<<" }\n";
}
void do_it(){
    ifstream ifs{"../26th_Part/26-1binary_search_test.txt"};
    ofstream ofs{"../26th_Part/26-1binary_search_test.txt"};
    if (!ifs||!ofs) cerr << "File open error!\n";
    //生成随机测试用例
    for (int i = 0; i < 100; ++i) {
        string lab="rand_test_";
        make_test(ofs, lab + to_string(i), randint(500), 0, randint(50));
    }
    //半系统测试
    int err_cnt= test_all(ifs);
    cout<<"numbers of errors: "<<err_cnt<<endl;
}
int main(){
    using namespace chrono;
    int n=1000;
    auto time_begin=system_clock::now();
    for (int i = 0; i < n; ++i) {
        do_it();
    }
    auto time_end=system_clock::now();
    cout<<"test "<<n<<" times took "<<duration_cast<milliseconds>(time_end-time_begin).count()/1000.0<<" seconds\n";
}