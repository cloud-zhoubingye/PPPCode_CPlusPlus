//
// Created by Zhou on 2023/2/12.
//
#include"../Head/std_lib_facilities.h"
class Link
{
public:
    string value;       //当前存储的字符串
    Link(const string& v,Link*prev= nullptr,Link*succ= nullptr)
            :value{v},previous{prev},succeed{succ}{}
    Link* insert(Link*insert_ahead);
    Link* add(Link*insert_after);
    Link*erase();
    Link*find(const string& target_string);
    const Link*find(const string&target_string)const;   //在const列表中查找target_string
    Link*advance(int n)const;
    Link*next()const{return succeed;}
    Link*prior()const{return previous;}
private:
    Link*previous;      //前一个
    Link*succeed;       //后一个
};

Link* Link::insert(Link*insert_ahead)
//在current之前插入insert_ahead
{
    if (this== nullptr) return this;
    if (insert_ahead== nullptr) return insert_ahead;
    //current紧跟在insert_ahead的后一个位置（将insert_ahead的后面接入）
    insert_ahead->succeed=this;
    //insert_ahead的前驱变更为current的前驱（将insert_ahead的前面接入）
    insert_ahead->previous=previous;
    //insert_ahead紧跟在current的原先前驱的后面（将原前驱的后面改成insert_ahead）
    if (previous!= nullptr)  previous->succeed=insert_ahead;
    //insert_ahead变为current的前驱（将原来项改在insert_ahead的后面）
    previous=insert_ahead;
    return insert_ahead;
}
Link* Link::add(Link*insert_after)
//在current之后插入insert_ahead
{
    if (this== nullptr) return this;
    if (insert_after== nullptr) return insert_after;
    //将insert_after前面接入
    insert_after->previous=this;
    //将insert_after后面接入
    insert_after->succeed=succeed;
    //将原先current的后面的前驱改为insert_after
    if (succeed!= nullptr) succeed->previous=insert_after;
    //将current的后面变更为insert_after
    succeed=insert_after;
    return insert_after;
}
Link*Link::erase()
//从链表中删除delete_item，并返回它的后面一个
{
    if (this== nullptr) return this;
    if (succeed!= nullptr) succeed->previous= previous;
    if (previous!= nullptr) previous->succeed= succeed;
    return succeed;
}
Link*Link::find(const string& target_string)
//在链表中查找s，返回nullptr表示未找到
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
//在链表中移动n个位置，n>0向succeed方向，n<0向previous方向，返回nullptr表示移动超出了链表的首尾
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

    //修改
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
