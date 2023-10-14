//
// Created by Zhou on 2023/3/9.
//

#include"../Head/std_lib_facilities.h"
const vector<string>total_name={
       "����һ","���ƽ",\
"�����","��ǧ��","������","��ܷܷ","������",\
"¬����","��־��","���ٺ�","������","�˿�",\
"�ƺ�","����ԭ","����Խ","���",\
"�ⶥ��","���Ω","������","���","���Ӻ�",\
"֣����","������","����","������",\
"���Ž�","����","��־��","��˼�","��ҵ��",\
"������","�ܱ���","���ƴ�","�����","����ͩ",\
"�����","�ƽ���","����Ϊ",\
"������","�곣��","����",\
"ĸ��˧","����","������","�˲���","��Զ��"};
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
    cout<<"����������������ѧϰ��ͬѧ������\n����\"OVER\"�Ա�ʾ����\n";
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
    cout<<"���������ѧϰ��δ��ɵ�ͬѧ�У�\n";
    for (string s:finished) {
        cout<<s<<endl;
        count++;
    }
    cout<<"�뻹û����ɱ��ܵ������ѧϰ�� "<<count<<" λͬѧ�������Ŷ��зз��\n\n\n";
}
void keep_the_window_open(char target_ch){
    cout<<"������\""<<target_ch<<"\"�Թرմ���!\n";
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




