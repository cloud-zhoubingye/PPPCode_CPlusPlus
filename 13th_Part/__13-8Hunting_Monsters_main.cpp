//
// Created by Zhou on 2023/2/25.
//
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>

using namespace std;
const int SAFE=0;
const int MONSTER=1;
const int PITFALL=2;
const int BIG_BAT=3;

class Shot_Input_Error{};       //抛出的输入射击信息错误
class Move_Input_Error{};       //抛出的输入移动信息错误
class Shot_Or_Move_Error{};     //抛出的输入移动还是射击信息错误

class Room{
public:
    Room(){Content=SAFE;}       //构造函数初始化房间的内容为安全
    int content()const{return Content;}      //返回房间的内容
    void set_content(const int room_content){Content=room_content;}      //设置房间的内容
    vector<int> connect_room()const{return Connect_room;}       //返回与之相连的房间号
    vector<int>& set_connect_room(){return Connect_room;}       //修改与之相连的房间号
private:
    int Content;        //房间的内容
    vector<int>Connect_room;        //与之相连的房间号
};
class Hole{
public:
    int room_cnt()const{return Room_cnt;}       //返回房间数
    void set_room_cnt(const int room_cnt){Room_cnt=room_cnt;}       //设置房间数
    int big_bat_number()const{return Big_bat_number;}       //返回蝙蝠数
    int& set_big_bat_number(){return Big_bat_number;}       //设置蝙蝠数
    int trap_number()const{return Trap_number;}     //返回陷阱数
    int& set_trap_number(){return Trap_number;}     //设置陷阱数
    vector<Room> rooms()const{return Rooms;}        //返回存储所有房间内容的vector
    vector<Room>& set_rooms(){return Rooms;}        //改变存储所有房间内容的vector
private:
    int Room_cnt;       //总房间数
    int Big_bat_number;         //蝙蝠数量
    int Trap_number;         //陷阱数量
    int Monster_place;      //怪兽所在的位置
    vector<Room> Rooms;         //存储所有房间内容的vector
};
class Shot{
public:
    int first_shot()const{return First_shot;}
    int second_shot()const{return Second_shot;}
    int third_shot()const{return Third_shot;}
    void set_first_shot(const int first_shot){First_shot=first_shot;}
    void set_second_shot(const int second_shot){Second_shot=second_shot;}
    void set_third_shot(const int third_shot){Third_shot=third_shot;}
private:
    int First_shot;
    int Second_shot;
    int Third_shot;
};
class Move{
public:
    int move_to()const{return Move_to;}
    void set_move_to(int moving_to_the_room){Move_to=moving_to_the_room;}
private:
    int Move_to;
};
class Game{
public:
    int monster_place()const{return Monster_place;}
    int& set_monster_place(){return Monster_place;}
    int user_place()const{return User_place;}
    int&set_user_place(){return User_place;}
    int sword_number()const{return Sword_number;}
    int& set_sword_number(){return Sword_number;}
    void use_sword(){--Sword_number;}
    Hole my_hole()const{return My_hole;}
    Hole&set_my_hole(){return My_hole;}
private:
    int Monster_place;
    int User_place;
    int Sword_number;
    Hole My_hole;
};

int base()      //存储自动生成的房间数的基数(总是它的倍数)
{
    static const int BASE=4;
    return BASE;
}
int lowest_room_number()        //存储自动生成的最小房间数
{
    static const int LOWEST_ROOM_NUMBER=16;
    return LOWEST_ROOM_NUMBER;
}
int highest_room_number()        //存储自动生成的最大房间数
{
    static const int HIGHEST_ROOM_NUMBER=64;
    return HIGHEST_ROOM_NUMBER;
}
string input_shot_error()       //存储射击输入信息错误的输出提示语句
{
    static const string str_shot_sorry="Sorry, the shooting information you entered is in the wrong format. \n";
    static const string str_shot_re_enter="Please refer to the following format to re-enter:\n";
    static const string str_shot_format="Reference input format:\ns-13-4-3\n";
    return str_shot_sorry+str_shot_re_enter+str_shot_format;
}
string input_shot_reminder()       //存储提示用户输入射击信息的提示语句
{
    static const string str_shot_reminder="Please enter your shot information:\n> ";
    return str_shot_reminder;
}
string input_move_error()       //存储射击输入信息错误的输出提示语句
{
    static const string str_move_sorry="Sorry, the moving information you entered is in the wrong format. \n";
    static const string str_move_re_enter="Please refer to the following format to re-enter:\n";
    static const string str_move_format="Reference input format:\nm-13\n";
    return str_move_sorry+str_move_re_enter+str_move_format;
}
string input_move_reminder()       //存储提示用户输入移动信息的提示语句
{
    static const string str_move_reminder="Please enter your move information:\n> ";
    return str_move_reminder;
}
string pitfall_game_over()       //存储用户因掉入陷阱而游戏失败的输出语句
{
    static const string str_pitfall_game_over="Sorry, you fell into the trap! \nYou are FAILED!\nGame Over!\n";
    return str_pitfall_game_over;
}
string monster_game_over()       //存储用户因掉入陷阱而游戏失败的输出语句
{
    static const string str_monster_game_over="Sorry, you are eaten by the monster! \nYou are FAILED!\nGame Over!\n";
    return str_monster_game_over;
}
string connect_monster_reminder()       //存储用户所在房间的相连接房间内有怪兽的危险提示语句
{
    static const string str_connect_monster_reminder="Dangerous!\nI smell a monster!\n";
    return str_connect_monster_reminder;
}
string connect_pitfall_reminder()       //存储用户所在房间的相连接房间内有陷阱的危险提示语句
{
    static const string str_connect_pitfall_reminder="Dangerous!\nI feel a breeze blowing!\n";
    return str_connect_pitfall_reminder;
}
string connect_big_bat_reminder()       //存储用户所在房间的相连接房间内有蝙蝠的危险提示语句
{
    static const string str_connect_big_bat_reminder="Dangerous!\nI hear the sound of a big bat!\n";
    return str_connect_big_bat_reminder;
}
string ask_shot_or_move(const Game&game)       //存储询问用户希望射击还是移动的语句
{
    static const string str_ask_shot_or_move1="You are currently in the room ";
    const string str_ask_shot_or_move2= to_string(game.user_place());
    static const string str_ask_shot_or_move3=" ,this room are connected to room";
    string str_ask_shot_or_move4;
    for(int room_number:game.my_hole().rooms()[game.user_place()].connect_room())
    {
        str_ask_shot_or_move4+=(' '+ to_string(room_number)+' '+','+' ');
    }
    const string str_ask_shot_or_move5="\nYour swords left:"+ to_string(game.sword_number())+'\n';
    static const string str_ask_shot_or_move6="Now, you have two options!\nMove or Shot ?\n> ";
    return str_ask_shot_or_move1+str_ask_shot_or_move2+str_ask_shot_or_move3+str_ask_shot_or_move4+str_ask_shot_or_move5+str_ask_shot_or_move6;
}
string input_move_or_shot_error()       //存储询问用户希望射击还是移动的输入信息错误的输出提示语句
{
    static const string str_input_move_or_shot_error="Sorry, the information you entered is in the wrong format.\nPlease re-enter:\n> ";
    return str_input_move_or_shot_error;
}
string kill_the_monster()       //成功杀死怪兽的提示语句
{
    static const string str_kill_the_monster="Congratulations!\nYou successfully killed the monster!\nThe game is successful!\n";
    return str_kill_the_monster;
}
string kill_the_big_bat()       //成功杀死蝙蝠的提示语句
{
    static const string str_kill_the_big_bat="Congratulations!\nYou successfully killed the big_bat!\nLet's go on! Good luck!\n";
    return str_kill_the_big_bat;
}

void initialize_game(Hole&hole,int&monster_locate,int&sword_number) ;     //初始化设置
void initialize_monster(Hole&hole,int&monster_locate) ;      //初始化怪兽位置
int initialize_room_number(int& room_number) ;       //自动生成一个房间数
bool is_initial_room_number_valid(const int room_number) ;       //判断自动生成的房间数是否合法
void set_room_vector_numbers(const int room_number, vector<Room>& Rooms) ;     //将Hole下的vector的元素个数设置为房间数
bool is_big_bat_number_valid(const int big_bat_number,const int room_number) ;       //检查自动生成的蝙蝠数是否合法
bool is_trap_number_valid(const int trap_number,const int room_number) ;       //检查自动生成的陷阱数是否合法
void set_big_bat_place(vector<Room>& Rooms, const int big_bat_number) ;        //随机生成蝙蝠位置并放置
int big_bat_place_number(int left_side,int right_side) ;     //在 ( left_side,right_side ] 之间生成一个蝙蝠所在的位置
void set_big_bat_numbers(const int room_number,int& big_bat_number) ;        //自动生成蝙蝠数量
void set_trap_numbers(const int room_number,int& trap_number) ;        //自动生成陷阱数量
bool is_trap_and_big_bat_collision(const vector<Room>&Rooms,int trap_place) ;    //检测陷阱和蝙蝠是否冲突
int trap_place_number(int left_side,int right_side,const vector<Room>&Rooms) ;     //在 ( left_side,right_side ] 之间生成一个蝙蝠所在的位置
void set_trap_place(vector<Room>& Rooms, const int trap_number) ;        //随机生成陷阱位置并放置
void set_big_bat_and_trap(vector<Room>& Rooms,int& big_bat_number,int& trap_number) ;    //设置蝙蝠和陷阱
bool connection_not_repeated(const Room&this_room,const int will_be_connected_room_number) ;       //检测房间相连情况是否无重复
int set_connect_room_number(const int room_size,const int cnt) ;      //设置相连的房间号
void connect_to(Room&connecting_to,const int number_of_connecting_to,Room&to_be_connected,const int number_of_to_be_connected) ;       //链接两个房间
void assign_room_connections(vector<Room>&Rooms) ;      //分配房间的随机相连关系
void assign_basic_ordinal_room_connections(vector<Room>&Rooms) ;       //分配基础顺序的房间的相连关系，确保每一个都相连
void set_connect_rooms(vector<Room>& Rooms) ;    //设置房间相连关系
void initialize_room_vector(const int room_number,Hole&hole) ;       //初始化房间的陷阱和蝙蝠
bool is_monster_repeated_with_others(const vector<Room>& Rooms,const int monster_place) ;    //检测怪兽位置是否和其他冲突
void get_three_times_shot_from_line(string& line,Shot&shot) ;     //从输入行中提取射击信息
void get_shot(Shot&shot) ;    //获取用户射击信息
void get_movement_from_line(string& line,Move&move) ;    //从输入行中提取移动信息
void get_move(Move&move) ;    //获取用户移动信息
void throw_by_big_bat(Game&game) ;       //被蝙蝠抓住扔进另一个房间
void move_to(Game&game,int moving_to) ;      //执行用户移动
void move(Game&game) ;        //读取并执行用户移动
void reminder(Game&game) ;    //用户进入每个房间后的提示信息
void is_shot_success_output(int my_shot) ;       //是否击中怪兽或蝙蝠的输出
void is_shot_success(const Shot&shot,const Game&game) ;     //是否击中怪兽或蝙蝠
void shot(Game&game) ;       //读取并执行用户射击
void shot_or_move(Game&game) ;       //询问用户是执行射击还是移动
void start_game(Game&game);      //启动游戏
void initialize_user_place(Game&game);       //初始化用户位置

/*
 * 以下是初始化部分
 * 提供的函数接口为：
 * void initialize(Hole&hole);
 */
int initialize_room_number(int& room_number)       //自动生成一个房间数
{
    srand(time(nullptr));
    room_number=rand()%highest_room_number();
    return room_number;
}
bool is_initial_room_number_valid(const int room_number)        //判断自动生成的房间数是否合法
{
    if(room_number%base()==0)
    {
        if(room_number>=lowest_room_number()&&room_number<=highest_room_number())
        {
            return true;
        }
    }
    return false;
}
void set_room_vector_numbers(const int room_number, vector<Room>& Rooms)      //将Hole下的vector的元素个数设置为房间数
{
    for (int i = 0; i < room_number; ++i)
    {
        Rooms.push_back(Room{});
    }
}
bool is_big_bat_number_valid(const int big_bat_number,const int room_number)        //检查自动生成的蝙蝠数是否合法
{
    if (big_bat_number>=(room_number/base())/2)
    {
        if (big_bat_number <= (room_number / base()))
        {
            if (big_bat_number > 0)
            {
                return true;
            }
        }
    }
    return false;
}
void set_big_bat_numbers(const int room_number,int& big_bat_number)         //自动生成蝙蝠数量
{
    srand(time(nullptr));
    for(;;)
    {
        big_bat_number=rand()%(room_number/base());
        if(is_big_bat_number_valid(big_bat_number,room_number))
        {
            break;
        }
    }
}
int big_bat_place_number(int left_side,int right_side)      //在 ( left_side,right_side ] 之间生成一个蝙蝠所在的位置
{
    srand(time(nullptr));
    int place=rand()%(right_side-left_side);
    for(;;){
        if(left_side==0)
        {
            if(place>=0&&place<=right_side) break;
        }
        else
        {
            if(place>0&&place<=right_side) break;
        }
        place=rand()%(right_side-left_side);
    }
    return place;
}
void set_big_bat_place(vector<Room>& Rooms, const int big_bat_number)         //随机生成蝙蝠位置并放置
{
    vector<int>big_bat_place;
    //生成
    int big_bat_interval=Rooms.size()/big_bat_number;
    for (int i = 0; i < big_bat_number; ++i)
    {
        int place= big_bat_place_number(big_bat_interval*i,big_bat_interval*(i+1));
        big_bat_place.push_back(place);
    }
    //放置
    for(int place:big_bat_place)
    {
        Rooms[place].set_content(BIG_BAT);
    }
}
bool is_trap_number_valid(const int trap_number,const int room_number)        //检查自动生成的陷阱数是否合法
{
    if (trap_number>=(room_number/base())/2)
        if (trap_number<=(room_number/base()))
            if (trap_number>0)
            {
                return true;
            }
    return false;
}
void set_trap_numbers(const int room_number,int& trap_number)         //自动生成陷阱数量
{
    srand(time(nullptr));
    for(;;)
    {
        trap_number=rand()%(room_number/base());
        if(is_trap_number_valid(trap_number,room_number))
        {
            break;
        }
    }
}
bool is_trap_and_big_bat_collision(const vector<Room>&Rooms,int trap_place)     //检测陷阱和蝙蝠是否冲突
{
    if(Rooms[trap_place].content()==BIG_BAT)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int trap_place_number(int left_side,int right_side,const vector<Room>&Rooms)      //在 ( left_side,right_side ] 之间生成一个蝙蝠所在的位置
{
    srand(time(nullptr));
    int place=rand()%(right_side-left_side);
    for(;;)
    {
        if(left_side==0)
        {   //如果是首个区间，则可以取[left
            if(place>=0&&place<=right_side)
            {
                if(!is_trap_and_big_bat_collision(Rooms,place))
                {
                    break;
                }
            }
        }
        else if(Rooms.size()-1-right_side<(Rooms.size())/base())
        {   //如果是最后一个区间，则可以取到区间最最末尾
            if(place>0&&place<=Rooms.size()-1)
            {
                if(!is_trap_and_big_bat_collision(Rooms,place))
                {
                    break;
                }
            }
        }
        else
        {
            if(place>0&&place<=right_side)
            {     //其他，则是( left_side,right_side ]
                if(!is_trap_and_big_bat_collision(Rooms,place))
                {
                    break;
                }
            }
        }
        place=rand()%(right_side-left_side);
    }
    return place;
}
void set_trap_place(vector<Room>& Rooms, const int trap_number)         //随机生成陷阱位置并放置
{
    int trap_interval=(Rooms.size()-1)/trap_number;
    for (int i = 0; i < trap_number; ++i)
    {
        int place=trap_place_number(trap_interval*i,trap_interval*(i+1),Rooms);
        Rooms[place].set_content(PITFALL);
    }
}
void set_big_bat_and_trap(vector<Room>& Rooms,int& big_bat_number,int& trap_number)     //设置蝙蝠和陷阱
{
    set_big_bat_numbers(Rooms.size(),big_bat_number);
    set_big_bat_place(Rooms,big_bat_number);
    set_trap_numbers(Rooms.size(),trap_number);
    set_trap_place(Rooms,trap_number);
}
bool connection_not_repeated(const Room&this_room,const int will_be_connected_room_number)        //检测房间相连情况是否无重复
{
    for(int con_room:this_room.connect_room())
    {
        if(con_room==will_be_connected_room_number)
        {
            return false;
        }
    }
    return true;
}
int set_connect_room_number(const int room_size,const int cnt)       //设置相连的房间号
{
    int connect_room_number=rand()%(room_size-1);
    int room_range=room_size/base();
    for(;;)
    {
        if(connect_room_number>cnt*room_range-base()&&connect_room_number>=0)
        {
            if (connect_room_number<(cnt+1)*room_range+base()&&connect_room_number<room_size)
            {
                break;
            }
        }
        room_range=room_size/base();
    }
    return connect_room_number;
}
void connect_to(Room&connecting_to,const int number_of_connecting_to,Room&to_be_connected,const int number_of_to_be_connected)        //链接两个房间
{
    connecting_to.set_connect_room().push_back(number_of_to_be_connected);
    to_be_connected.set_connect_room().push_back(number_of_connecting_to);
}
void assign_room_connections(vector<Room>&Rooms)       //分配房间的随机相连关系
{
    for(;;)
    {
        srand(::time(nullptr));
        for(int this_room=0; this_room < Rooms.size(); ++this_room)
        {
            for(int cnt=0; cnt<(Rooms.size()/base()); cnt++)
            {
                int connect_room_number= set_connect_room_number(Rooms.size(),cnt);
                if(connection_not_repeated(Rooms[this_room],connect_room_number))
                {
                    connect_to(Rooms[this_room],this_room,Rooms[connect_room_number],connect_room_number);
                }
            }
        }
    }
}
void assign_basic_ordinal_room_connections(vector<Room>&Rooms)        //分配基础顺序的房间的相连关系，确保每一个都相连
{
    for (int i = 0; i < Rooms.size(); ++i)
    {
        if (i==Rooms.size()-1)
        {
            if(connection_not_repeated(Rooms[i],0))
            {
                connect_to(Rooms[i],i,Rooms[0],0);
            }
        }
        else
        {
            if(connection_not_repeated(Rooms[i],i+1))
            {
                connect_to(Rooms[i],i,Rooms[i+1],i+1);
            }
        }
    }
}
void set_connect_rooms(vector<Room>& Rooms)     //设置房间相连关系
{
    assign_room_connections(Rooms);
    assign_basic_ordinal_room_connections(Rooms);
}
void initialize_room_vector(const int room_number,Hole&hole)        //初始化房间的陷阱和蝙蝠
{
    set_room_vector_numbers(room_number,hole.set_rooms());
    set_big_bat_and_trap(hole.set_rooms(),hole.set_big_bat_number(),hole.set_trap_number());
    set_connect_rooms(hole.set_rooms());
}
bool is_monster_repeated_with_others(const vector<Room>& Rooms,const int monster_place)     //检测怪兽位置是否和其他冲突
{
    if(Rooms[monster_place].content()!=SAFE)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void initialize_monster(Hole&hole,int&monster_locate)       //初始化怪兽位置
{
    srand(time(nullptr));
    int monster_place=rand()%(hole.room_cnt()-1);
    for(;;)
    {
        if(!is_monster_repeated_with_others(hole.rooms(),monster_place))
        {
            hole.set_rooms()[monster_place].set_content(MONSTER);
            monster_locate=monster_place;
            break;
        }
    }
}
void initialize_game(Hole&hole,int&monster_locate,int&sword_number)      //初始化设置
{
    sword_number=5;
    int room_number=0;
    while(!is_initial_room_number_valid(initialize_room_number(room_number)))
    { }
    initialize_room_vector(room_number,hole);
    initialize_monster(hole,monster_locate);
}

/*
 *以下是游戏进行部分
 * 提供的函数接口为：
 *
 */
void get_three_times_shot_from_line(string& line,Shot&shot)     //从输入行中提取射击信息
{
    for (char&ch:line)
    {
        if(ch=='-'){
            ch=' ';
        }
    }
    int first=0,second=0,third=0;
    char shot_sign=0;
    stringstream ss{line};
    ss>>shot_sign>>first>>second>>third;
    if(!ss||shot_sign!='s')
    {
        throw Shot_Input_Error{};
    }
    shot.set_first_shot(first);
    shot.set_second_shot(second);
    shot.set_third_shot(third);
}
void get_shot(Shot&shot)     //获取用户射击信息
{
    for(;;)
    {
        try
        {
            cout<<input_shot_reminder;
            string line;
            getline(cin,line);
            get_three_times_shot_from_line(line,shot);
            break;
        }
        catch (Shot_Input_Error)
        {
            cerr<<input_shot_error();
        }
    }
}
void get_movement_from_line(string& line,Move&move)     //从输入行中提取移动信息
{
    for (char&ch:line)
    {
        if(ch=='-'){
            ch=' ';
        }
    }
    int movement;
    char move_sign=0;
    stringstream ss{line};
    ss>>move_sign>>movement;
    if(!ss||move_sign!='m')
    {
        throw Move_Input_Error{};
    }
    move.set_move_to(movement);
}
void get_move(Move&move)     //获取用户移动信息
{
    for(;;)
    {
        try
        {
            cout<<input_move_reminder();
            string line;
            getline(cin,line);
            get_movement_from_line(line,move);
            break;
        }
        catch (Move_Input_Error)
        {
            cerr<<input_move_error();
        }
    }
}
void throw_by_big_bat(Game&game)        //被蝙蝠抓住扔进另一个房间
{
    srand(time(nullptr));
    int throwing_to_vector=rand()%(game.my_hole().rooms()[game.user_place()].connect_room().size());
    int throwing_to=game.my_hole().rooms()[game.user_place()].connect_room()[throwing_to_vector];
    move_to(game,throwing_to);
}
void move_to(Game&game,int moving_to)       //执行用户移动
{
    game.set_user_place()=moving_to;
    if(game.my_hole().rooms()[moving_to].content()==BIG_BAT)
    {
        throw_by_big_bat(game);
    }
    else if (game.my_hole().rooms()[moving_to].content()==PITFALL)
    {
        cout<<pitfall_game_over();
        exit(0);
    }
    else if (game.my_hole().rooms()[moving_to].content()==MONSTER)
    {
        cout<<monster_game_over();
        exit(0);
    }
    else
    {
        reminder(game);
    }
}
void move(Game&game)         //读取并执行用户移动
{
    Move move;
    get_move(move);
    game.set_user_place()=move.move_to();
    move_to(game,move.move_to());
}
void reminder(Game&game)     //用户进入每个房间后的提示信息
{
    for (int connect_room:game.my_hole().rooms()[game.user_place()].connect_room())
    {
        switch (connect_room)
        {
            case SAFE:
                break;
            case MONSTER:
                cout<<connect_monster_reminder();
                break;
            case PITFALL:
                cout<<connect_pitfall_reminder();
                break;
            case BIG_BAT:
                cout<<connect_big_bat_reminder();
                break;
        }
    }
}
void is_shot_success_output(int my_shot)        //是否击中怪兽或蝙蝠的输出
{
    switch (my_shot)
    {
        case MONSTER:
        {
            cout<<kill_the_monster();
            exit(0);
        }
        case BIG_BAT:
        {
            cout<<kill_the_big_bat();
        }
    }
}
void is_shot_success(const Shot&shot,const Game&game)      //是否击中怪兽或蝙蝠
{
    cout<<"About your first sword\n";
    is_shot_success_output(game.my_hole().rooms()[shot.first_shot()].content());
    cout<<"About your second sword\n";
    is_shot_success_output(game.my_hole().rooms()[shot.second_shot()].content());
    cout<<"About your third sword\n";
    is_shot_success_output(game.my_hole().rooms()[shot.third_shot()].content());
}
void shot(Game&game)        //读取并执行用户射击
{
    Shot shot;
    game.use_sword();
    get_shot(shot);
    is_shot_success(shot,game);
    if (game.sword_number()==0)
    {
        cout<<"Failed!\nYou have no more sword!\nGame Over!\n";
        exit(0);
    }
}
void shot_or_move(Game&game)        //询问用户是执行射击还是移动
{
    cout<<ask_shot_or_move(game);
    for(;;)
    {
        try
        {
            char ch_sign;
            cin>>ch_sign;
            if (ch_sign=='s')
            {
                cin.putback(ch_sign);
                shot(game);
            }
            else if(ch_sign=='m')
            {
                cin.putback(ch_sign);
                move(game);
            }
            else
            {
                throw Shot_Or_Move_Error{};
            }
            break;
        }
        catch (Shot_Or_Move_Error)
        {
            cerr<<input_move_or_shot_error();
        }
    }
}
void initialize_user_place(Game&game)       //初始化用户位置
{
    srand(time(nullptr));
    int begin_user_place=rand()%(game.my_hole().room_cnt()-1);
    for(;;)
    {
        if(game.my_hole().rooms()[begin_user_place].content()==SAFE)
        {
            break;
        }
        else
        {
            begin_user_place=rand()%(game.my_hole().room_cnt()-1);
        }
    }
    game.set_user_place()=begin_user_place;
    reminder(game);
}
void start_game(Game&game)      //启动游戏
{
    initialize_game(game.set_my_hole(),game.set_monster_place(),game.set_sword_number());
    initialize_user_place(game);
    shot_or_move(game);
}
int main(){ Game game;start_game(game);}