#include <cassert>
#include <iostream>
#include <cmath>
#include "../src/Circle.hpp"

int main() {
    std::cout << "========== Circle Class Tests ==========" << std::endl;
    
    // Test default constructor
    {
        Circle c;
        assert(c.getRadius() == 0);
        assert(c.getCenter().getX() == 0 && c.getCenter().getY() == 0);
        std::cout << "Default constructor: PASSED" << std::endl;
    }
    
    // Test parameterized constructor with Point
    {
        Point center(3.0, 4.0);
        Circle c(center, 5.0);
        assert(c.getRadius() == 5.0);
        assert(c.getCenter().getX() == 3.0 && c.getCenter().getY() == 4.0);
        std::cout << "Parameterized constructor with Point: PASSED" << std::endl;
    }
    
    // Test parameterized constructor with coordinates
    {
        Circle c(1.0, 2.0, 3.0);
        assert(c.getRadius() == 3.0);
        assert(c.getCenter().getX() == 1.0 && c.getCenter().getY() == 2.0);
        std::cout << "Parameterized constructor with coordinates: PASSED" << std::endl;
    }
    
    // Test copy constructor
    {
        Circle original(1.0, 2.0, 3.0);
        Circle copy(original);
        assert(copy.getRadius() == 3.0);
        assert(copy.getCenter().getX() == 1.0 && copy.getCenter().getY() == 2.0);
        std::cout << "Copy constructor: PASSED" << std::endl;
    }
    
    // Test assignment operator
    {
        Circle original(4.0, 5.0, 6.0);
        Circle assigned;
        assigned = original;
        assert(assigned.getRadius() == 6.0);
        assert(assigned.getCenter().getX() == 4.0 && assigned.getCenter().getY() == 5.0);
        std::cout << "Assignment operator: PASSED" << std::endl;
    }
    
    // Test setters
    {
        Circle c;
        Point newCenter(7.0, 8.0);
        c.setCenter(newCenter);
        c.setRadius(9.0);
        assert(c.getRadius() == 9.0);
        assert(c.getCenter().getX() == 7.0 && c.getCenter().getY() == 8.0);
        std::cout << "Setters: PASSED" << std::endl;
    }
    
    // Test area calculation
    {
        Circle c(0.0, 0.0, 2.0);
        double expectedArea = M_PI * 4.0; // π * r²
        assert(fabs(c.getArea() - expectedArea) < 1e-6);
        std::cout << "Area calculation: PASSED" << std::endl;
    }
    
    // Test circumference calculation
    {
        Circle c(0.0, 0.0, 2.0);
        double expectedCircumference = 2.0 * M_PI * 2.0; // 2πr
        assert(fabs(c.circumference() - expectedCircumference) < 1e-6);
        std::cout << "Circumference calculation: PASSED" << std::endl;
    }
    
    // Test equality operators
    {
        Circle c1(1.0, 2.0, 3.0);
        Circle c2(1.0, 2.0, 3.0);
        Circle c3(4.0, 5.0, 6.0);
        
        assert(c1 == c2);
        assert(!(c1 == c3));
        assert(c1 != c3);
        assert(!(c1 != c2));
        
        std::cout << "Equality operators: PASSED" << std::endl;
    }
    
    // Test print method
    {
        Circle c(3.0, 4.0, 5.0);
        std::cout << "Print test (should show center at (3,4) with radius 5): ";
        c.print();
        
    }
    
    std::cout << "All Circle class tests PASSED!" << std::endl;
    return 0;
}