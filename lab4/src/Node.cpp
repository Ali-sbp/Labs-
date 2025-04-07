#include "Node.hpp"
#include "Circle.hpp"

Node::Node() : pPrev(nullptr) , pNext(nullptr) , m_Data() {}

//parameter constructor
Node::Node(Node* prev, Node* next, const Circle* pc) : pPrev(prev) , pNext(next), m_Data(*pc) {
    if (prev) prev->pNext = this;
    if (next) next->pPrev = this;
}


//destructor
Node::~Node() {
    if (pPrev) pPrev->pNext = pNext;
    if (pNext) pNext->pPrev = pPrev;
    
}
//getters
Node* Node::getPrev()const{
    return pPrev;
}
Node* Node::getNext()const{
    return pNext;
}
Circle& Node::getData(){
    return m_Data;
}
const Circle& Node::getData()const{
    return m_Data;
}

//setters
void Node::setPrev(Node* prev){
    pPrev = prev;
}
void Node::setNext(Node* next){
    pNext = next;
}
void Node::setData(const Circle& data){
    m_Data = data;
}


