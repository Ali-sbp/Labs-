#include <iostream>
#include <cassert>
#include "../src/rect.hpp"

using namespace std;
int main() {
  
    rect r1(2, 6, 12, 4);

    //check width
    //assert(r1.get_width() == 6 - 2);  
    assert(r1.get_width() == 12);
    //check height
    //assert(r1.get_height() == 12 - 4);
    assert(r1.get_height() == 4);
    //check square
    assert(r1.get_square() == r1.get_width() * r1.get_height());

    //check set_width method
    r1.set_width(10); // 
    assert(r1.get_width() == 10);
    //assert(r1.get_right() == r1.get_left() + 10); 

    //check set_height method
    r1.set_heigth(6); 
    assert(r1.get_height() == 6); 
    //assert(r1.get_top() == r1.get_bottom() + 6);

    cout << "properties test passed!" <<endl;
    return 0;
}
