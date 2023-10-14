//
// Created by Zhou on 2023/2/12.
//
#include"../Head/std_lib_facilities.h"
class Link
{
public:
    string value;       //��ǰ�洢���ַ���
    Link(const string& v,Link*prev= nullptr,Link*succ= nullptr)
            :value{v},previous{prev},succeed{succ}{}
    Link* insert(Link*insert_ahead);
    Link* add(Link*insert_after);
    Link*erase();
    Link*find(const string& target_string);
    const Link*find(const string&target_string)const;   //��const�б��в���target_string
    Link*advance(int n)const;
    Link*next()const{return succeed;}
    Link*prior()const{return previous;}
private:
    Link*previous;      //ǰһ��
    Link*succeed;       //��һ��
};

Link* Link::insert(Link*insert_ahead)
//��current֮ǰ����insert_ahead
{
    if (this== nullptr) return this;
    if (insert_ahead== nullptr) return insert_ahead;
    //current������insert_ahead�ĺ�һ��λ�ã���insert_ahead�ĺ�����룩
    insert_ahead->succeed=this;
    //insert_ahead��ǰ�����Ϊcurrent��ǰ������insert_ahead��ǰ����룩
    insert_ahead->previous=previous;
    //insert_ahead������current��ԭ��ǰ���ĺ��棨��ԭǰ���ĺ���ĳ�insert_ahead��
    if (previous!= nullptr)  previous->succeed=insert_ahead;
    //insert_ahead��Ϊcurrent��ǰ������ԭ�������insert_ahead�ĺ��棩
    previous=insert_ahead;
    return insert_ahead;
}
Link* Link::add(Link*insert_after)
//��current֮�����insert_ahead
{
    if (this== nullptr) return this;
    if (insert_after== nullptr) return insert_after;
    //��insert_afterǰ�����
    insert_after->previous=this;
    //��insert_after�������
    insert_after->succeed=succeed;
    //��ԭ��current�ĺ����ǰ����Ϊinsert_after
    if (succeed!= nullptr) succeed->previous=insert_after;
    //��current�ĺ�����Ϊinsert_after
    succeed=insert_after;
    return insert_after;
}
Link*Link::erase()
//��������ɾ��delete_item�����������ĺ���һ��
{
    if (this== nullptr) return this;
    if (succeed!= nullptr) succeed->previous= previous;
    if (previous!= nullptr) previous->succeed= succeed;
    return succeed;
}
Link*Link::find(const string& target_string)
//�������в���s������nullptr��ʾδ�ҵ�
{
    Link*p=this;
    while(p!= nullptr){
        if (p->value==target_string)
            return p;
        else
            p=p->succeed;
    }
    return nullptr;
}
Link* Link::advance(int n)const
//���������ƶ�n��λ�ã�n>0��succeed����n<0��previous���򣬷���nullptr��ʾ�ƶ��������������β
{
    Link*p=const_cast<Link*>(this);
    if (this== nullptr)
        return p;
    if (n<0) {
        for (; n != 0; n--) {
            if (p->previous == nullptr)
                return nullptr;
            p = p->previous;
        }
    }
    if (n>0){
        for(;n!=0;n--) {
            if (p->succeed == nullptr)
                return nullptr;
            p = p->succeed;
        }
    }
    return p;
}
void print_all(Link*p)
{
    cout<<"{ ";
    while(p!= nullptr){
        cout<<p->value;
        if ((p=p->next())!= nullptr)
            cout<<", ";
    }
    cout<<" }"<<endl;
}
int main()
{
    Link*norse_gods=new Link{"Thor"};
    norse_gods= norse_gods->insert(new Link{"Odin"});
    norse_gods= norse_gods->insert(new Link{"Zeus"});
    norse_gods= norse_gods->insert(new Link{"Freia"});

    Link*greek_gods=new Link{"Hera"};
    greek_gods= greek_gods->insert(new Link{"Athena"});
    greek_gods= greek_gods->insert(new Link{"Mars"});
    greek_gods= greek_gods->insert(new Link{"Poseidon"});

    //�޸�
    Link*p=greek_gods->find("Mars");
    if (p!= nullptr){
        p->value="Ares";
    }
    p= norse_gods->find("Zeus");
    if (p!= nullptr){
        if (p==norse_gods) norse_gods=p->next();
        p->erase();
        greek_gods= greek_gods->insert(p);
    }
    print_all(norse_gods);
    print_all(greek_gods);
}
