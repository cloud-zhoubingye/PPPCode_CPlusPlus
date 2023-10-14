//
// Created by Zhou on 2023/2/2.
//

#include "Punctuate_Stream.h"
bool Punctuate_Stream::is_whitespace (const char &ch)const
{
    for (const char&white_ch :white)
    {
        if (white_ch==ch)
            return true;
    }
    return false;
}
Punctuate_Stream& Punctuate_Stream::operator>>(string& s)
{
    cout<<"BUFFER:"<<buffer.str()<<":BUFFER\n";
    while(!(buffer>>s)) //���buffer���Ѿ�Ϊ��
    {
        if(buffer.bad()||input_source.fail()||input_source.eof())   //��������
            return *this;
        buffer.clear();
        string line;
        getline(input_source,line);
        for (char&ch:line)
        {
            if(is_whitespace(ch))   //�滻�ָ���
                ch=' ';
            else if (!is_case_sensitive())  //ת����Сд
                ch=tolower(ch);
        }
        //����buffer
        buffer.str(line);
    }
    return *this;
}
Punctuate_Stream::operator bool()
{
    //��good���Ҳ���fail����bad�ſ��Է���true
    return (!(input_source.fail()||input_source.bad()))&&input_source.good();
}
int main()
{
    const string white_string=";:,.?!()\"{}<>/&$@#%^*|~";
    Punctuate_Stream ps {cin};
    ps.whitespace(white_string);
    ps.set_case_sensitive(false);
    cout<<"Please enter words:\n";
    vector<string>word;
    for (string input_word;ps>>input_word;)
    {
        word.push_back(input_word);
    }
    //����
    sort(word.begin(),word.end());
        //ȥ��
        vector<string> out_word;
        for (int i = 0; i < word.size(); ++i) {
            if (i == 0 || word[i] == word[i - 1])
                out_word.push_back(word[i]);
        }
    for(string s:out_word)
        cout<<s<<endl;

    return 0;
}