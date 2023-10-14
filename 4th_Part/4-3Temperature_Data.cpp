#include"../Head/std_lib_facilities.h"
int main()
{
	//��������
	vector<double> temperature;
	double temp;
	cout << "�����¶�\t(�������λ,��������������ַ�����ֹ����!)��\n";
	while (cin>>temp)
	{
		temperature.push_back(temp);
	}
	//��ƽ��ֵ
	double sum = 0;
	for (int x : temperature)
	{
		sum += x;
	}
	double average = sum / temperature.size();
	cout << "\nAverage: " << average << '\n';
	//����λ����������
	sort(temperature);
	double middle;
	if (temperature.size()%2==1)
	{
		//����������λ��Ϊ�м��Ǹ�
		middle = temperature[temperature.size() / 2];
	}
	else
	{
		//ż��������λ��Ϊ�м�����ƽ��ֵ
		middle = (temperature[temperature.size() / 2 - 1] + temperature[temperature.size() / 2]) / 2.0;
	}
	cout << "Middle: " << middle << '\n';
	cout << "Highest: " << temperature[temperature.size() - 1] << '\n';
	cout << "lowest: " << temperature[0] << '\n';
}