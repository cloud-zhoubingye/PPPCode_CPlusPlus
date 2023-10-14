#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
//vectorµÄÄÚÈİ------------------------------------------------------------------------------

inline void print_vector_int(const vector<int>& v) { cout << "Print Vector: \n"; for (int x : v) { cout << x << '\n'; } }
inline void print_vector_string(const vector<string>& v) { cout << "Print Vector: \n"; for (string x : v) { cout << x << '\n'; } }
inline void input_vector_string(vector<string>& v) { string x; while (cin >> x) { v.push_back(x); } }
inline void input_vector_int(vector<int>& v) { int x; while (cin >> x) { v.push_back(x); } }