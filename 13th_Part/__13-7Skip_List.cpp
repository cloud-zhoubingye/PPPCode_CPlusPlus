//
// Created by Zhou on 2023/2/25.
//
#include "../Head/std_lib_facilities.h"
template<typename T> class Skip_Node {
public:
    Skip_Node(const int index, const T &value, const int index_level);

private:
    int Index;
    T Value;
    vector<Skip_Node *> Next;
};
template<typename T>Skip_Node<T>::Skip_Node(const int index,const T&value,const int index_level)
    :Index{index},Value{value}{
    for (int i = 0; i < index_level; ++i) {
        Next.push_back(nullptr);
    }
}
template<typename T> class Skip_List{
public:
            //构造函数
            Skip_List();
private:
        };