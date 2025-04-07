#include <cassert>
#include <iostream>
#include <cmath>
#include "../src/Point.hpp"

int main() {
    std::cout << "========== Point Class Tests ==========" << std::endl;
    
    // Test default constructor
    {
        Point p;
        assert(p.getX() == 0 && p.getY() == 0);
        std::cout << "Default constructor: PASSED" << std::endl;
    }
    
    // Test parameterized constructor
    {
        Point p(3.5, 4.5);
        assert(p.getX() == 3.5 && p.getY() == 4.5);
        std::cout << "Parameterized constructor: PASSED" << std::endl;
    }
    
    // Test copy constructor
    {
        Point original(2.0, 3.0);
        Point copy(original);
        assert(copy.getX() == 2.0 && copy.getY() == 3.0);
        std::cout << "Copy constructor: PASSED" << std::endl;
    }
    
    // Test assignment operator
    {
        Point original(5.0, 6.0);
        Point assigned;
        assigned = original;
        assert(assigned.getX() == 5.0 && assigned.getY() == 6.0);
        std::cout << "Assignment operator: PASSED" << std::endl;
    }
    
    // Test setters
    {
        Point p;
        p.setX(7.5);
        p.setY(8.5);
        assert(p.getX() == 7.5 && p.getY() == 8.5);
        std::cout << "Setters: PASSED" << std::endl;
    }
    
    // Test distance calculation
    {
        Point p1(0, 0);
        Point p2(3, 4);
        assert(fabs(p1.Distance(p2) - 5.0) < 1e-6);
        
        Point p3(1, 1);
        Point p4(4, 5);
        assert(fabs(p3.Distance(p4) - 5.0) < 1e-6);
        
        std::cout << "Distance calculation: PASSED" << std::endl;
    }
    
    // Test origin distance
    {
        Point p(3, 4);
        assert(fabs(p.OriginDistance() - 5.0) < 1e-6);
        std::cout << "Origin distance: PASSED" << std::endl;
    }
    
    // Test equality operators
    {
        Point p1(1.0, 2.0);
        Point p2(1.0, 2.0);
        Point p3(3.0, 4.0);
        
        assert(p1 == p2);
        assert(!(p1 == p3));
        assert(p1 != p3);
        assert(!(p1 != p2));
        
        std::cout << "Equality operators: PASSED" << std::endl;
    }
    
    // Test print method
    {
        Point p(7.5, 8.5);
        std::cout << "Print test (should show x=7.5, y=8.5): ";
        p.print();
        
    }
    
    std::cout << "All Point class tests PASSED!" << std::endl;
    return 0;
}