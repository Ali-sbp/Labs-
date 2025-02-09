#include <iostream>
#include <cassert>
#include "../src/rect.hpp"

using namespace std;

int main() {
    //defult constructor
    rect r1;
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);
    
    //paramets constructor
    rect r2(1, 5, 10, 3);
    assert(r2.get_left() == 1);
    assert(r2.get_right() == 5);
    assert(r2.get_top() == 10);
    assert(r2.get_bottom() == 3);

    //copy constructor
    rect r3 = r2;
    assert(r3.get_left() == r2.get_left());
    assert(r3.get_right() == r2.get_right());
    assert(r3.get_top() == r2.get_top());
    assert(r3.get_bottom() == r2.get_bottom());

    //set_all method
    r1.set_all(2, 6, 12, 4);
    assert(r1.get_left() == 2);
    assert(r1.get_right() == 6);
    assert(r1.get_top() == 12);
    assert(r1.get_bottom() == 4);

    cout << "basic methods test passed!" <<endl;
    return 0;
}
