#include "rect.hpp"
#include <iostream>

using namespace std;
 //1.11
rect bounding_rect(rect r1, rect r2){
        int new_left= min(r1.get_left(), r2.get_left());
        int new_right= max(r1.get_right(),r2.get_right());
        int new_top= max(r1.get_top(),r2.get_top());
        int new_bottom= min(r1.get_bottom(), r2.get_bottom());
        return rect(new_left, new_right, new_top, new_bottom); 
    }
//1.11
void print_rect(const rect &r) {
    r.display();
}

/*int main (){
    // 1.12
     rect r1(1,2,3,4), r2(5,6,7,8);
        rect r3 = bounding_rect(r1, r2);
        print_rect(r3);

    rect r5(1,2,3,4); 
    r5.set_width(10);
    print_rect(r5); 
   
    return 0;
}*/