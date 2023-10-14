#include"../Head/std_lib_facilities.h"
ifstream& operator>>(ifstream& ifs, vector<string>&text)
{
	for (string in_txt; ifs >> in_txt;)
	{
		text.push_back(in_txt);
	}
	return ifs;
}
ofstream& operator<<(ofstream& ofs, vector<string>& text)
{
	for (size_t i = 0; i < text.size(); i++)
	{
		ofs << text[i] << '\n';
	}
	return ofs;
}
int main()
{
	ifstream is1{ "D:\\My_C++_Programme\\C++������ƣ�ԭ����ʵ��\\10-4����ȡ�ĵ���1.txt" };
	ifstream is2{ "D:\\My_C++_Programme\\C++������ƣ�ԭ����ʵ��\\10-4����ȡ�ĵ���2.txt" };
	vector<string>text;
	is1 >> text;
	is2 >> text;
	is1.close();
	is2.close();
	sort(text);
	ofstream ofs{ "D:\\My_C++_Programme\\C++������ƣ�ԭ����ʵ��\\10-4�ϲ������������ļ�.txt" };
	ofs << "NEW TEXT : \n\n";
	ofs << text;
	ofs.close();
	cout << "Finished!\n";
}