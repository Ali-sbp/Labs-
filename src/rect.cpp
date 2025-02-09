#include "rect.hpp"
#include <iostream>

using namespace std;
//null const 
rect::rect() : left(0),right(0),top(0),bottom(0) {
    cout<<"null constructor called, object addess:"<<this<<endl;
}
rect::rect(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {
    cout<<"parameter constructor called, object addess:"<<this<<endl;
}
rect::rect(const rect &other):  left(other.left) , right(other.right) , top(other.top) , bottom(other.bottom){
    cout<<"copy constructor called ,object addess:"<<this<<endl;
}
rect::~rect()  {
    cout<<"destructor called"<<endl;
}

// getters 

    int rect::get_left() {return left;}
    int rect::get_right() {return right;}
    int rect::get_top() {return top;}
    int rect::get_bottom() {return bottom;}
    int rect::get_width() {return right-left;}
    int rect::get_height() {return top-bottom;}
    int rect::get_square(){return (get_width() * get_height());}

    //setters 

    void rect::set_all (int a, int b, int c, int d) { 
        left = a;
        right =b;
        top = c;
        bottom= d;
    }
    void rect::set_width (int w){
        if (left<right){
            right = left + w;
        }
        else left= right + w;
    }
    void rect::set_heigth (int h){
        if (bottom < top){
            top = bottom + h;
        }
        else bottom = top + h;
    }
   

    void rect::inflate (int amount) {
        left = left - amount;
        right = right + amount;
        top = top + amount;
        bottom = bottom - amount;
    }
    void rect::inflate (int dw, int dh){
        left = left - dw;
        right = right + dw;
        top = top + dh;
        bottom = bottom - dh;
    }
    
    void rect::move (int a=0, int b=0){
        left+= a;
        right+= a;
        top+= b;
        bottom += b;

    }
    void rect::display () const {  
        cout<< "rect: left="<<left<<"right= "<<right<<"top= "<<top<<"bottom= "<<bottom<<endl;
    }

rect bounding_rect(rect r1, rect r2){
        int new_left= min(r1.get_left(), r2.get_left());
        int new_right= max(r1.get_right(),r2.get_right());
        int new_top= max(r1.get_top(),r2.get_top());
        int new_bottom= min(r1.get_bottom(), r2.get_bottom());
        return rect(new_left, new_right, new_top, new_bottom); 
    }

void print_rect(const rect &r) {
    r.display();
}

