#include"../Head/std_lib_facilities.h"
#include<math.h>
int main()
{
	unsigned long long rice = 0, total_rice = 0;
	int checkerboard;
	for (checkerboard = 1; checkerboard <= 64; checkerboard++)
	{
		rice = pow(2, checkerboard - 1);
		total_rice += rice;
		cout << "��" << checkerboard << "������ʢ�ŵĴ�������Ϊ" << rice << "\n"
			<< "�ܹ������Ѿ�������" << total_rice << "������\n\n";
	}
}