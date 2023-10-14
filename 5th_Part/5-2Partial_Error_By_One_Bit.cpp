#include"../Head/std_lib_facilities.h"
int main()
{
	try
	{
		vector<int>v;
		for (int x = 0; cin>>x; )
		{
			v.push_back(x);
		}
		for (int i = 0; i <= v.size(); i++)
		{
			//vector���±꺯�����Զ��ӳ�out_of_range
			cout << "v[" << i << "]==" << v[i] << '\n';
		}
	}
	catch (out_of_range)
	{
		cout << "Oops! Range Error!\n";
		return 1;
	}
}