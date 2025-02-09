#include <iostream>
#include <algorithm>
#ifndef RECT_HPP
#define RECT_HPP

using namespace std;

class rect {
    private:
    int left,right,top,bottom;
    public:
    
    //default constructor
   /*rect()  {
        cout<<"default constructor called, object address:"<<this<<endl;
    }*/

    // null constructor
    rect () : left(0),right(0),top(0),bottom(0) {
         cout<<"null constructor called, object addess:"<<this<<endl;
    }
   
   
   //parametr constructor
    rect(int l,int r,int t,int b) : left(l), right(r), top(t), bottom(b) {
        cout<<"parameter constructor called, object addess:"<<this<<endl;
    }


   //copy constructor
    rect (const rect& Original) 
    :  left(Original.left) , right(Original.right) , top(Original.top) , bottom(Original.bottom){
        cout<<"copy constructor called ,object addess:"<<this<<endl;
    }

    ~rect () {
        cout<<"destructor called"<<endl;
    }

    //getters 

    int get_left() {return left;}
    int get_right() {return right;}
    int get_top() {return top;}
    int get_bottom() {return bottom;}
    int get_width() {return right-left;}
    int get_height() {return top-bottom;}
    int get_square(){return (get_width() * get_height());}

    //setters 
    void set_all (int a, int b, int c, int d) { 
        left = a;
        right =b;
        top = c;
        bottom= d;
    }
    void set_width (int w){
        if (left<right){
            right = left + w;
        }
        else left= right + w;
    }
    void set_heigth (int h){
        if (bottom < top){
            top = bottom + h;
        }
        else bottom = top + h;
    }
   

    void inflate (int amount) {
        left = left - amount;
        right = right + amount;
        top = top + amount;
        bottom = bottom - amount;
    }
    void inflate (int dw, int dh){
        left = left - dw;
        right = right + dw;
        top = top + dh;
        bottom = bottom - dh;
    }
    /*void move (int a){
        left = left + a;
        right = right + a;
    }*/
    void move (int a=0, int b=0){
        left+= a;
        right+= a;
        top+= b;
        bottom += b;

    }
    void display () const {  
        cout<< "rect: left="<<left<<"right= "<<right<<"top= "<<top<<"bottom= "<<bottom<<endl;
    }

   friend rect bounding_rect (rect r1, rect r2);

   friend void print_rect (const rect &r); 
    
    
};

#endif //RECT_HPP