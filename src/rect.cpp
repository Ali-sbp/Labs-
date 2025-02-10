#include "rect.hpp"
#include <iostream>

using namespace std;
//null const 
/*rect::rect() : left(0),right(0),top(0),bottom(0) {
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
}*/
rect::rect() : BLx(0),BLy(0),width(0),height(0) {
    cout<<"null constructor called, object addess:"<<this<<endl;
}
rect::rect(int x, int y, int w, int h) : BLx(x), BLy(y), width(w), height(h) {
    cout<<"parameter constructor called, object addess:"<<this<<endl;
}
rect::rect(const rect &other):  BLx(other.BLx) , BLy(other.BLy) , width(other.width) , height(other.height){
    cout<<"copy constructor called ,object addess:"<<this<<endl;
}
rect::~rect()  {
    cout<<"destructor called"<<endl;
}

// getters 

    //int rect::get_left()const {return left;}
    int rect::get_BLx() const{return BLx;}
    //int rect::get_right() const{return right;}
    int rect::get_BLy()const {return BLy;}
    //int rect::get_top()const {return top;}
    //int rect::get_bottom()const {return bottom;}
    int rect::get_width()const {return width;} //changed 
    int rect::get_height()const {return height;} //changed 
    int rect::get_square()const{return (get_width() * get_height());}

    //setters 

    void rect::set_all (int a, int b, int c, int d) { 
        //left = a;
        BLx=a;
        //right =b;
        BLy=b;
        //top = c;
        width=c;
        //bottom= d;
        height=d;
    }
    void rect::set_width (int w){
        /*if (left<right){
            right = left + w;
        }
        else left= right + w;*/
        width=w;
    }
    void rect::set_heigth (int h){
       /* if (bottom < top){
            top = bottom + h;
        }
        else bottom = top + h;*/
        height=h;
    }
   

    void rect::inflate (int amount) {
        //left = left - amount;
        BLx= BLx - amount;
        //right = right + amount;
        BLy=BLy - amount;
        //top = top + amount;
        width=width + (2*amount);
        //bottom = bottom - amount;
        height=height + (2* amount);
    }
    void rect::inflate (int dw, int dh){
        //left = left - dw;
        BLx= BLx - dw;
        //right = right + dw;
        BLy=BLy-dh;
        //top = top + dh;
        width=width+(2*dw);
        //bottom = bottom - dh;
        height= height +(2*dh);
    }
    
    void rect::move (int a, int b){
        //left+= a;
        BLx+=a;
        //right+= a;
        //top+= b;
        BLy+=b;
        //bottom += b;

    }
    void rect::display () const {  
        cout<< "rect: BLx="<<BLx<<"BLY= "<<BLy<<"width= "<<width<<"height= "<<height<<endl;
    }

    /*rect bounding_rect(rect r1, rect r2){
        int new_left= min(r1.get_left(), r2.get_left());
        int new_right= max(r1.get_right(),r2.get_right());
        int new_top= max(r1.get_top(),r2.get_top());
        int new_bottom= min(r1.get_bottom(), r2.get_bottom());
        return rect(new_left, new_right, new_top, new_bottom); 
    }*/
    rect bounding_rect(const rect& r1, const rect& r2) {
        
        int new_BLx = min(r1.get_BLx(), r2.get_BLx());
        int new_BLy = min(r1.get_BLy(), r2.get_BLy());
        
        int r1_right = r1.get_BLx() + r1.get_width();
        int r2_right = r2.get_BLx() + r2.get_width();
        int new_right = max(r1_right, r2_right);
        
        int r1_top = r1.get_BLy() + r1.get_height();
        int r2_top = r2.get_BLy() + r2.get_height();
        int new_top = max(r1_top, r2_top);
        
        int new_width = new_right - new_BLx;
        int new_height = new_top - new_BLy;
        
        return rect(new_BLx, new_BLy, new_width, new_height);
    }

void print_rect(const rect &r) {
    r.display();
}

