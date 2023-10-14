#include"../Head/std_lib_facilities.h"
void quadratic_equation(int a, int b, int c)
{
	int delta = b * b - 4 * a * c;
	double x = 0, y = 0;
	if (delta < 0)
	{
		throw runtime_error("�÷����޽�");
	}
	else if (delta == 0)
	{
		x = (double)-b / (2 * a);
		cout << "\nX= " << x << '\n';
	}
	else
	{
		x = (double)(-b + sqrt(delta)) / (2 * a);
		y = (double)(-b - sqrt(delta)) / (2 * a);
		cout << "\nX1= " << x << "\tX2= " << y << '\n';
	}
}
int main()
{
	try
	{
		int a = 0, b = 0, c = 0;
		cout << "������һ��һԪ���η��̵ı�׼��ʽ(ax^2+bx+c=0)�µ�����ϵ��a,b,c(�ո����)\n";
		cin >> a >> b >> c;
		quadratic_equation(a, b, c);
	}
	catch (const std::exception&err)
	{
		cerr << "ERROR��" << err.what() << '\n';
	}
}