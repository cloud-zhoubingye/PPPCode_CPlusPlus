#include"../Head/std_lib_facilities.h"
int main()
{
	cout << "����һ������������(��þͲ������Ŷ)\t������1-100֮�������Ŷ\n"
		<< "����һ��ö��ٴ�������ܲ��У�\n���������7�����ʵĻ���Ŷ����Ҳ������Ϊ�Ҳ²���(��-1)��\n";
	int times = 0;
	int guess = 50, lowest = 0, highest = 100;
	cin >> times;
	for (size_t i = 1; i <=7; i++)
	{
		char input;
		cout << "�����������"<<guess<<"��?\n������y\t\t����õ�������������h\t����õ�������С����l\n";
		cin >> input;
		if (input=='y')
		{
			//�ɹ�
			cout << "\n�����������" << guess << "\n�һ���" << i << "�ξͲ�������\n";
			if (i==times)
			{
				cout << "������Ĵ���һ������������������Ϭ\n";
			}
			else
			{
				cout << "Ȼ����ȴ��Ϊ�Ҳ�����Ҫ " << times << " �Σ�";
				if (times>i)
				{
					cout << "����ȻС������!\n";
				}
				else
				{
					cout << "�������߹�������!\n";
				}
			}
			break;
		}
		else if (input=='h')
		{
			lowest = guess;
			guess = (guess + highest) / 2;
		}
		else if (input=='l')
		{
			highest = guess;
			guess = (guess + lowest) / 2;
		}
		else
		{
			cout << "ɵ�ƣ�����\n";
			return 0;
		}
	}
}