#ifndef WORKERDB_HPP
#define WORKERDB_HPP

#include "MyString.hpp"
#include <stdexcept>

// struct for worker data
struct WorkerData {
    MyString name;
    int age;
    double salary;
    
    // cons
    WorkerData() : name(), age(0), salary(0.0) {}
    WorkerData(const char* name_val, int age_val, double salary_val = 0.0) 
        : name(name_val), age(age_val), salary(salary_val) {}
};

// Forward declarations
class WorkerDb;
class WorkerDbIterator;

// WorkerDb class
class WorkerDb {
private:
    // node struct for linked list
    struct Node {
        MyString surname;  // key
        WorkerData data;   // value
        Node* next;        // pointer to next node
        
        // Constructor
        Node(const MyString& key) : surname(key), data(), next(nullptr) {}
    };
    
    Node* head;   
    size_t count; 
    
public:
    WorkerDb();
    ~WorkerDb();
    WorkerDb(const WorkerDb& other); 
    // assignment operator
    WorkerDb& operator=(const WorkerDb& other);
    
    // indexing operators / create worker if doesn't exist
    WorkerData& operator[](const char* surname);
    WorkerData& operator[](const MyString& surname);
    
    // size access
    size_t size() const;
    
    // Iterator methods (declarations only)
    WorkerDbIterator begin() const;
    WorkerDbIterator end() const;
    
    // friend declaration
    friend class WorkerDbIterator;
};

// iterator class - DEFINED AFTER WorkerDb
class WorkerDbIterator {
private:
    const WorkerDb* db;            // refrence to db
    WorkerDb::Node* current;       // current node pointer

public:
    // cons
    WorkerDbIterator(const WorkerDb* database, WorkerDb::Node* node)
        : db(database), current(node) {}
    
    // comparison op
    bool operator==(const WorkerDbIterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const WorkerDbIterator& other) const {
        return !(*this == other);
    }
    
    // increment operators
    // prefix
    WorkerDbIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }
    
    // postfix (it++)
    WorkerDbIterator operator++(int) {
        WorkerDbIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    // dereference op
    WorkerData& operator*() const {
        if (!current) {
            throw std::runtime_error("attempting to dereference null iterator");
        }
        return current->data;
    }
    
    WorkerData* operator->() const {
        if (!current) {
            throw std::runtime_error("attempting to access null iterator");
        }
        return &(current->data);
    }
    
    //key access
    const MyString& key() const {
        if (!current) {
            throw std::runtime_error("attempting to get key from null iterator");
        }
        return current->surname;
    }
};

//
inline WorkerDbIterator WorkerDb::begin() const {
    return WorkerDbIterator(this, head);
}

inline WorkerDbIterator WorkerDb::end() const {
    return WorkerDbIterator(this, nullptr);
}

#endif // WORKERDB_HPP