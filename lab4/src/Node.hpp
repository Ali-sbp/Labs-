#include "Point.hpp"
#include "Circle.hpp"

#ifndef NODE_HPP
#define NODE_HPP

class Node {
    private:
    Node* pPrev;
    Node* pNext;
    Circle m_Data;

    public:
    //constructors
    Node();
    Node(Node* prev, Node* next , const Circle* pc); 
    /*
        i wrote the entire code with Circle* pc in Node parametr constructor, 
        the problem that this brings is, at the end when you are creating these nodes, 
        and using this circle pointer, it assumes that this circle object exists somewhere. 
        if by any means this was the case in a test I ran!) this circle objects is deteled,
        then you have dangling pointers that go aaaaaaall the way from List objects to circles,
        which do not exist. by using refrance we save ourselves from the bug. I will not change
        to refrences because in lab4.docx in the template it used pointers and I went with it, 
        but consider this part please. 
    
    */
    //destructor
    ~Node();

    //getters
    Node* getPrev()const;
    Node* getNext()const;
    Circle& getData();
    const Circle& getData()const;

    //setters
    void setPrev(Node* prev);
    void setNext(Node* next);
    void setData(const Circle& data);

    friend class List;

};

#endif //NODE_HPP