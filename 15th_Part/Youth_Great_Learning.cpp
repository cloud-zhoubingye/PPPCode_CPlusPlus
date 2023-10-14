//
// Created by Zhou on 2023/3/9.
//

#include"../Head/std_lib_facilities.h"
const vector<string>total_name={
       "祁明一","王瀚平",\
"闫淑婕","曹千晔","蒋姿仪","孟芊芊","文润欣",\
"卢子轩","吴志恒","许少鸿","杨铭海","邓俊",\
"唐豪","王中原","符博越","李晨轩",\
"吴顶仲","杨瀚惟","范祥正","夏宇涵","张子豪",\
"郑栋藩","何清亮","戴成","付少文",\
"何昱剑","李仪","蔺志杰","刘思瑜","徐业垚",\
"张明明","周炳烨","邓善聪","刘晨睿","宋雨桐",\
"周正岚","唐锦康","张祥为",\
"陈昶文","申常鹏","徐赛",\
"母德帅","王宏","张玉祥","邓博文","何远超"};
vector<string>dormitory={
        "10--102","10--102",\
"10--102","10--201","10--201","10--201","10--201",\
"7--202","7--202","7--202","7--202","7--301",\
"7--301","7--301","7--301","7--301",\
"7--301","7--301","7--301","7--301","7--301",\
"7--301","7--302","7--302","7--302",\
"7--302","7--302","7--302","7--302","7--302",\
"7--302","7--302","7--401","7--401","7--401",\
"7--401","7--401","7--401",\
"7--401","7--401","7--401",\
"7--402","7--402","7--402","7--402","7--402"
};
void get_name(vector<string>&finished){
    cout<<"请输入已完成青年大学习的同学姓名：\n输入\"OVER\"以表示结束\n";
    for (string s;cin>>s;){
        if (s=="OVER")break;
        finished.push_back(s);
    }
}
bool is_not_finished(const string& s,const vector<string>&finished){
    for (string name:finished) {
        if (s==name) return false;
    }
    return true;
}
vector<string> not_finished(const vector<string>&finished){
    vector<string>not_finished(0);
    for (int i = 0; i < total_name.size(); ++i) {
        if (is_not_finished(total_name[i],finished)){
            string s=dormitory[i] +"--"+total_name[i];
            not_finished.push_back(s);
        }
    }
    return not_finished;
}
void print(const vector<string>&finished){
    int count=0;
    cout<<"本周青年大学习暂未完成的同学有：\n";
    for (string s:finished) {
        cout<<s<<endl;
        count++;
    }
    cout<<"请还没有完成本周的青年大学习的 "<<count<<" 位同学尽快完成哦，蟹蟹！\n\n\n";
}
void keep_the_window_open(char target_ch){
    cout<<"请输入\""<<target_ch<<"\"以关闭窗口!\n";
    char ch;
    while(cin.get(ch)&&ch!=target_ch){
    }
}
int main(){
    vector<string>finished;
    get_name(finished);
    print(not_finished(finished));
    keep_the_window_open('!');
}




