#include <iostream>
#include <cassert>
#include "../src/rect.hpp"

int main() {
   
    rect r1(2, 6, 12, 4);

    // inflate 1 arg
    r1.inflate(2); 
    assert(r1.get_left() == 0);  
    assert(r1.get_right() == 8); 
    assert(r1.get_top() == 14);  
    assert(r1.get_bottom() == 2); 

    // inflate 2 args
    r1.inflate(3, 4); 
    assert(r1.get_left() == -3);  
    assert(r1.get_right() == 11); 
    assert(r1.get_top() == 18);   
    assert(r1.get_bottom() == -2); 

    // move
    r1.move(5, 5);  
    assert(r1.get_left() == 2);  
    assert(r1.get_right() == 16); 
    assert(r1.get_top() == 23);  
    assert(r1.get_bottom() == 3); 

    cout<< "operations test passed!" <<endl;
    return 0;
}
