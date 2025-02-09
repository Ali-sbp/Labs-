#include <iostream>
#include <algorithm>
#ifndef RECT_HPP
#define RECT_HPP

using namespace std;

class rect {
    private:
    int left,right,top,bottom;
    public:
    

    // null constructor
    rect (); 
   
   
   //parametr constructor
    rect(int l,int r,int t,int b); 

   //copy constructor
    rect (const rect& other);
    

    ~rect ();

    //getters 

    int get_left();
    int get_right();
    int get_top();
    int get_bottom();
    int get_width();
    int get_height();
    int get_square();

    //setters 
    void set_all (int a, int b, int c, int d);

    void set_width (int w);

    void set_heigth (int h);

    void inflate (int amount);
    
    void inflate (int dw, int dh);
    
    void move (int a, int b);

    void display () const;

   friend rect bounding_rect (rect r1, rect r2);

   friend void print_rect (const rect &r); 
    
    
};

#endif //RECT_HPP