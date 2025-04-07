#include <cassert>
#include <iostream>
#include "../src/Node.hpp"

int main() {
    std::cout << "========== Node Class Tests ==========" << std::endl;
    
    // Test default constructor
    {
        Node n;
        assert(n.getPrev() == nullptr);
        assert(n.getNext() == nullptr);
        assert(n.getData().getRadius() == 0);
        std::cout << "Default constructor: PASSED" << std::endl;
    }
    
    // Test parameterized constructor
    {
        Node n1;
        Node n3;
        
        Circle* c = new Circle(1.0, 2.0, 3.0);
        Node* n2 = new Node(&n1, &n3, c);
        
        assert(n1.getNext() == n2);
        assert(n3.getPrev() == n2);
        assert(n2->getPrev() == &n1);
        assert(n2->getNext() == &n3);
        assert(n2->getData().getRadius() == 3.0);
        assert(n2->getData().getCenter().getX() == 1.0);
        assert(n2->getData().getCenter().getY() == 2.0);
        
        delete n2;
        delete c;
        std::cout << "Parameterized constructor: PASSED" << std::endl;
    }
    
    // Test setters
    {
        Node n1, n2, n3;
        
        n2.setPrev(&n1);
        n2.setNext(&n3);
        
        assert(n2.getPrev() == &n1);
        assert(n2.getNext() == &n3);
        
        Circle c(4.0, 5.0, 6.0);
        n2.setData(c);
        
        assert(n2.getData().getRadius() == 6.0);
        assert(n2.getData().getCenter().getX() == 4.0);
        assert(n2.getData().getCenter().getY() == 5.0);
        
        std::cout << "Setters: PASSED" << std::endl;
    }
    
    // Test auto-linking in constructor
    {
        Node n1, n3;
        Circle* c = new Circle(1.0, 2.0, 3.0);
        
        // This should automatically set n1.next = &n2 and n3.prev = &n2
        Node* n2 = new Node(&n1, &n3, c);
        
        assert(n1.getNext() == n2);
        assert(n3.getPrev() == n2);
        
        delete n2;
        delete c;
        std::cout << "Auto-linking in constructor: PASSED" << std::endl;
    }
    
    // Test destructor auto-unlinking
    {
        Node n1, n4;
        Circle* c1 = new Circle(1.0, 2.0, 3.0);
        Circle* c2 = new Circle(4.0, 5.0, 6.0);
        
        Node* n2 = new Node(&n1, nullptr, c1);
        Node* n3 = new Node(n2, &n4, c2);
        n2->setNext(n3);
        
        // Now we have: n1 <-> n2 <-> n3 <-> n4
        assert(n1.getNext() == n2);
        assert(n2->getNext() == n3);
        assert(n3->getNext() == &n4);
        assert(n4.getPrev() == n3);
        assert(n3->getPrev() == n2);
        assert(n2->getPrev() == &n1);
        
        // Delete n2 - should relink n1 <-> n3
        delete n2;
        assert(n1.getNext() == n3);
        assert(n3->getPrev() == &n1);
        
        // Delete n3 - should relink n1 <-> n4
        delete n3;
        assert(n1.getNext() == &n4);
        assert(n4.getPrev() == &n1);
        
        delete c1;
        delete c2;
        std::cout << "Destructor auto-unlinking: PASSED" << std::endl;
    }
    
    // Test getData const correctness
    {
        Circle* c = new Circle(1.0, 2.0, 3.0);
        const Node n(nullptr, nullptr, c);
        
        // This calls const version of getData()
        const Circle& circRef = n.getData();
        assert(circRef.getRadius() == 3.0);
        
        delete c;
        std::cout << "getData const correctness: PASSED" << std::endl;
    }
    
    std::cout << "All Node class tests PASSED!" << std::endl;
    return 0;
}