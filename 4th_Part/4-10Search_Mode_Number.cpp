#include"../Head/std_lib_facilities.h"
void find_mode(vector<int> num, int left, int right, int* mode, int* multiplicity);
int main()
{
	//��������
	vector<int>num;
	int input_number;
	while (cin >> input_number)
	{
		num.push_back(input_number);
	}
	//������
	sort(num);
    int mode_multiplicity = 0;
    int mode = 0;
    find_mode(num, 0, num.size() - 1, &mode, &mode_multiplicity);
    cout << "mode: " << mode << '\n'
        << "multiplicity: " << mode_multiplicity << "\n\n";
}
void find_mode(vector<int> num, int left, int right, int* mode, int* multiplicity)
{
    int center = (left + right) / 2;
    int cnt = 1;
    //�����߱����м���ֵ��ͬ�ĸ���
        //�ұ�
    int r;
    for (r = center+1; r <= right; r++)
    {
        if (num[center]==num[r])
        {
            cnt++;
        }
        else
        {
            break;
        }
    }
        //���
    int l;
    for (l = center-1; l >= left; l--)
    {
        if (num[center] == num[l])
        {
            cnt++;
        }
        else
        {
            break;
        }
    }
    //������������ͬ��������������
    if (cnt==*multiplicity)
    {
        //���õ��ĵ�һ�Σ���Ϊ�м��Ǹ������ִ���������Ϊ0
        //����ͬ������һ������������������Ǹ�
        *multiplicity = cnt;
        *mode = num[center];
    }
    //�������ԭ���Ǹ�����������
    if (cnt>*multiplicity)
    {
        *multiplicity = cnt;
        *mode = num[center];
    }
    //��ĳһ��ʣ��Ԫ�ظ�������Ŀǰ�����������ǰ����δ������������
        //�ұ�
    if (right - r > *multiplicity)
    {
        //�ݹ�����ұ�
        find_mode(num, r, right, mode, multiplicity);
    }
        //���
    if (l - left > *multiplicity)
    {
        //�ݹ�����ұ�
        find_mode(num, left, l, mode, multiplicity);
    }
}
