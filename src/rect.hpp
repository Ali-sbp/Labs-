#include <iostream>
#include <algorithm>
#ifndef RECT_HPP
#define RECT_HPP

using namespace std;

class rect {
    private:
    //int left,right,top,bottom;
    int BLx;
    int BLy;
    int width;
    int height;
    public:
    

    // null constructor
    rect (); 
   
   
   //parametr constructor
    rect(int x,int y,int w,int h); 

   //copy constructor
    rect (const rect& other);
    

    ~rect ();

    //getters 

    //int get_left()const;  didn't need to change , just changed for proper naming and commenting previous code.
    int get_BLx()const;
    //int get_right() const;
    int get_BLy()const;
    //int get_top()const;
    //int get_bottom()const;
    int get_width()const;
    int get_height()const;
    int get_square()const;

    //setters 
    void set_all (int a, int b, int c, int d);

    void set_width (int w);

    void set_heigth (int h);

    void inflate (int amount);
    
    void inflate (int dw, int dh);
    
    void move (int a=0, int b=0);

    void display () const;

   //friend rect bounding_rect (const rect &r1, const rect &r2);
   friend rect bounding_rect(const rect& r1, const rect& r2);

   friend void print_rect (const rect &r); 
    
    
};

#endif //RECT_HPP