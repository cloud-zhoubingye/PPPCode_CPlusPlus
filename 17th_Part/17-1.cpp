//
// Created by Zhou on 2023/3/24.
//
#include "../Head/std_lib_facilities.h"
#include "../Head/Graph.h"
#include "../Head/Simple_window.h"
int main(){
    using namespace Graph_lib;
    Point t{100,100};
    Simple_window win{t,600,400,"Canvas"};
    Polygon poly;
    poly.add(Point{300,200});
    poly.add(Point{350,100});
    poly.add(Point{400,200});
    poly.set_color(Color::red);
    win.attach(poly);
    win.wait_for_button();
}