#include"../Head/std_lib_facilities.h"
int main()
{
	//����ֵ�������
	cout << "������������������(�ո����)��" << '\n';
	int a = 0, b = 0, c = 0, mid = 0;
	cin >> a >> b >> c;
	if (a > b)
		swap(a, b);
	if (a>c)
	{
		swap(a, c);
	}
	if (b>c)
	{
		swap(b, c);
	}
	cout << a << ',' << b << ',' << c << '\n';

	//�ַ����������
	cout << "�����������ַ���(�ո����)��\n"<<"Chinese is also OK!\n";
	string x = " ", y = " ", z = " ";
	cin >> x >> y >> z;
	if (x>y)
	{
		swap(x, y);
	}
	if (x>z)
	{
		swap(x, z);
	}
	if (y>z)
	{
		swap(y, z);
	}
	cout << x << ',' << y << ',' << z << '\n';
}