//
// Created by Zhou on 2023/2/25.
//
//VECTOR2.0
//含普通初始化，列表初始化
//支持深拷贝和移动语义
#include"../Head/std_lib_facilities.h"
class  VECTOR
{
private:
    int size_of_vector;      //大小
    double* elements;     //指向元素的指针
public:
    VECTOR(int length);    //构造函数
    VECTOR(initializer_list<double>list);       //初始化器列表构造函数
    VECTOR(const VECTOR&arg);    //拷贝构造函数
    VECTOR& operator=(const VECTOR&arg);        //拷贝赋值函数
    ~VECTOR();       //析构函数
    VECTOR(VECTOR&&arg);        //移动构造函数
    VECTOR& operator=(VECTOR&&arg);      //移动赋值

    int size()const;
    double get(int n)const;
    void set(int n,double num);
};
VECTOR::VECTOR(int length)    //构造函数
        :size_of_vector{length},elements{new double[length]}
{
    for (int i = 0; i < size_of_vector; ++i){
        elements[i] = 0.0;      //初始化
    }
}
VECTOR::VECTOR(initializer_list<double>list)     //初始化器列表构造函数
        :size_of_vector{static_cast<int>(list.size())},elements{new double[size_of_vector]}
{
    copy(list.begin(),list.end(),elements);
}
VECTOR::VECTOR(const VECTOR&arg)    //拷贝构造函数
        :size_of_vector{arg.size_of_vector},elements{new double[size_of_vector]}
{
    copy(arg.elements,arg.elements+arg.size_of_vector,elements);
}
VECTOR::~VECTOR()       //析构函数
{
    delete[] elements;
}
int VECTOR::size()const
{
    return size_of_vector;
}
double VECTOR::get(int n)const
{
    return elements[n];
}
void VECTOR::set(int n,double num)
{
    elements[n]=num;
}
VECTOR& VECTOR::operator=(const VECTOR&arg)
{
    size_of_vector=arg.size_of_vector;      //拷贝vector大小
    double*p_elem=new double[size_of_vector];       //申请存储数据的新空间
    copy(arg.elements,arg.elements+arg.size_of_vector,p_elem);      //拷贝数组到存储数据的新空间
    delete[] elements;        //释放旧空间
    elements=p_elem;        //使原数组指向存储数据的新空间
    return *this;       //返回vector的自引用
}
VECTOR::VECTOR(VECTOR&&arg)        //移动构造函数
        :size_of_vector{arg.size_of_vector},elements{arg.elements}
{
    arg.size_of_vector=0;
    arg.elements= nullptr;      //还没有分配，所以无需delete，直接置空即可
}

VECTOR& VECTOR::operator=(VECTOR &&arg)      //移动赋值
{
    size_of_vector=arg.size_of_vector;      //拷贝size
    delete[] elements;      //释放待移动到的对象的旧空间
    elements=arg.elements;      //把待移动到的对象的element指向原对象的
    arg.elements= nullptr;      //改变原对象的element指向
    arg.size_of_vector=0;       //将原对象的size改为0
    return *this;
}
int main()
{
    VECTOR v{2,3,4,5,6,7,8,9};
    for (int i = 0; i < v.size(); ++i) {
        cout<<"V["<<i<<"]=="<<fixed<<v.get(i)<<endl;
    }
    v=v;
    for (int i = 0; i < v.size(); ++i) {
        cout<<"V1["<<i<<"]=="<<fixed<<v.get(i)<<endl;
    }
}
