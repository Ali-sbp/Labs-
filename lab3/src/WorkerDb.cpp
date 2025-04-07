#include "WorkerDb.hpp"
#include <stdexcept>

WorkerDb::WorkerDb() : head(nullptr), count(0) {}
WorkerDb::~WorkerDb() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
//copy cons
WorkerDb::WorkerDb(const WorkerDb& other) : head(nullptr), count(0) {
    Node* src = other.head;
    while (src) {
        //using [] to create and fill the node
        (*this)[src->surname] = src->data;
        src = src->next;
    }
}

//assignment op
WorkerDb& WorkerDb::operator=(const WorkerDb& other) {
    if (this != &other) {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        count = 0;
        Node* src = other.head;
        while (src) {
            (*this)[src->surname] = src->data;
            src = src->next;
        }
    }
    return *this;
}

//aaccess operator using const char*
WorkerData& WorkerDb::operator[](const char* surname) {
    return (*this)[MyString(surname)];
}

//access operator using MyString
WorkerData& WorkerDb::operator[](const MyString& surname) {
    //finding
    Node* current = head;
    while (current) {
        if (current->surname == surname) {
            return current->data;
        }
        current = current->next;
    }
    
    //create new if not found
    Node* newNode = new Node(surname);
    
    //put in head
    newNode->next = head;
    head = newNode;
    count++;
    
    return newNode->data;
}

//get size
size_t WorkerDb::size() const {
    return count;
}