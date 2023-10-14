#include"../Head/std_lib_facilities.h"
int main()
{
	//��ȫ��ת��
		//int<����>char
	cout << "��ȫ��ת��\n";
	char c = 'x';
	int i = c;
	char c1 = i;
	cout << "int<����>char\n";
	cout << c << ' ' << i << ' ' << c1 << '\n';
		//int<����>double
	double d1 = 2.3, d2 = d1 + 2;
	cout << "int<����>double\n";
	cout << d1 << ' ' << d2 << '\n';
	//����ȫ��ת������խ��ת��
	cout << "\n����ȫ��ת��\n";
	int a = 20000;
	c = a;
	int b = c;
	cout << a << ' ' << c << ' ' << b << '\n';
	//ͨ��ͳһ��ʼ����{ }�б�Ǻ�
	double x1{ 2.7 };
	int y1{ x1 };					//�����޷�ͨ�������ӡ�double��ת������int����Ҫ����ת��
	int x2{ 1000 };
	char y2{ x2 };					//�����޷�ͨ�������ӡ�int��ת������char����Ҫ����ת��
}
