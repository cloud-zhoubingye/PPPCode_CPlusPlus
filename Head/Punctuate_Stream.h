//
// Created by Zhou on 2023/2/2.
//
#include "std_lib_facilities.h"
#ifndef C__PRINCIPLES_AND_PRACTISE_PUNCTUATE_STREAM_H
#define C__PRINCIPLES_AND_PRACTISE_PUNCTUATE_STREAM_H
class Punctuate_Stream
{
public:
    Punctuate_Stream(istream&is)
            :input_source{is},punctuate_sensitive{true}{}
    void whitespace(const string& s){white=s;}
    void add_whitespace(const string& s){white+=s;}
    bool is_whitespace (const char& ch)const;
    void set_case_sensitive(const bool& is_sensitive){punctuate_sensitive=is_sensitive;}
    bool is_case_sensitive() const{return punctuate_sensitive;}

    Punctuate_Stream& operator>>(string& s);
    operator bool();
private:
    istream& input_source;
    istringstream buffer;   //��Ϊ������
    string white;
    bool punctuate_sensitive;
};
#endif //C__PRINCIPLES_AND_PRACTISE_PUNCTUATE_STREAM_H
