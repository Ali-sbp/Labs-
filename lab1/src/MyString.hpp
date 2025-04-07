#ifndef MYSTRING_HPP
#define MYSTRING_HPP

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
//get,set
char get(int i) const; 
void set(int i ,char c);
void set_new_string(const char* new_string);
void print() const;
void read_line();
};



#endif //MYSTRING_HPP