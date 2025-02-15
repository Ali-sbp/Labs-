#include <iostream>
#include <cassert>
#include "../src/rect.hpp"

using namespace std;
int main() {
   
    rect r1(1, 5, 10, 3);
    rect r2(3, 7, 12, 5);

    //non overlapping rects
    rect bounding = bounding_rect(r1, r2);
    assert(bounding.get_left() == 1);   
    assert(bounding.get_right() == 15);  
    assert(bounding.get_top() == 12);   
    assert(bounding.get_bottom() == 5);
    //rect bounding = bounding_rect(r1, r2);
    /*assert(bounding.get_BLx() == 1);  
    assert(bounding.get_BLy() == 5);  
    assert(bounding.get_width() == (3 + 12 - 1));  
    assert(bounding.get_height() == (7 + 5 - 5));*/

    //swapped left and right input
    rect r3(5, 1, 10, 3);  
    rect bounding2 = bounding_rect(r1, r3);
    assert(bounding2.get_left() == 1);  
    assert(bounding2.get_right() == 15); 
    //rect r3(5, 1, 10, 3);
    //rect bounding2 = bounding_rect(r1, r3);
    /*assert(bounding2.get_BLx() == 1);
    assert(bounding2.get_width() == (5 + 10 - 1));*/

    //swapped top and bottom input
    rect r4(1, 5, 3, 10); 
    rect bounding3 = bounding_rect(r1, r4);
    assert(bounding3.get_top() == 15);   
    assert(bounding3.get_bottom() == 5); 
    //rect r4(1, 5, 3, 10);
    //rect bounding3 = bounding_rect(r1, r4);
    /*assert(bounding3.get_BLy() == 5);
    assert(bounding3.get_height() == (5 + 10 - 5));*/

    cout << "bounding rect test passed!" <<endl;
    return 0;
}
