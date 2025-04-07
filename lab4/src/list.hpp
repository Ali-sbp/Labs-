#include "Node.hpp"
#include "Circle.hpp"
#include <iostream>
#include <fstream>
#include <cstddef>


#ifndef LIST_HPP
#define LIST_HPP

class List {

    private:
    Node Head;
    Node Tail;
    size_t M_size;

    public:
    //constructors
    List();
    List(Node head,Node tail,size_t m_size);
    //destructor
    ~List();

    //methods
    void addToFront(const Circle& c); // changed to refrance after debugging , was Circle* c before.
    void addToEnd(const Circle& c);
    bool removeFirst(const Circle& c);
    size_t removeAll(const Circle& c);
    void clear();
    size_t size()const;
    bool isEmpty() const;
    void sort();

    //optional methods
    Node* find(const Circle& c)const;
    Circle* getCircleAt(size_t index) const;
    size_t countCirclesWithRadiusGreaterThan(double radius) const;

    //I/O operations
    friend std::ostream& operator<<(std::ostream& os, const List& list);
    void saveToFile(const std::string& filename)const;
    void loadFromFile(const std::string& filename);

    //helper functions
    //edge cases
    //empty files
    //performance optimizations?
};

#endif //LIST_HPP