#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <iostream>

class MyString
{
private:
    char* string;
    int length; 
public:
//default const
MyString();
//const char input
MyString(const char* input);
//copy
MyString(const MyString &other);
//destructor
~MyString();
//assignment operator
MyString& operator=(const MyString &other); 
//get,set
char get(int i) const; 
void set(int i ,char c);
void set_new_string(const char* new_string);
void print() const;
void read_line();
//operators 
MyString& operator+=(const MyString& other);
MyString& operator+=(const char* str);
MyString operator+(const MyString& other) const;
MyString operator+(const char* str) const;
friend MyString operator+(const char* str, const MyString& s);
bool operator==(const MyString& other) const;
bool operator!=(const MyString& other) const;
bool operator<(const MyString& other) const;
bool operator<=(const MyString& other) const;
bool operator==(const char* str) const;
bool operator!=(const char* str) const;
bool operator<(const char* str) const;
bool operator<=(const char* str) const;
friend bool operator<(const char* str, const MyString& s);
char& operator[](int i);
const char& operator[](int i) const;
friend std::ostream& operator<<(std::ostream& os, const MyString& s);
friend std::istream& operator>>(std::istream& is, MyString& s);
};
MyString operator+(const char* str, const MyString& s);

bool operator==(const char* str, const MyString& s);
bool operator!=(const char* str, const MyString& s);
bool operator<=(const char* str, const MyString& s);



#endif //MYSTRING_HPP