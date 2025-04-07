#include "MyString.hpp"
#include <iostream>
#include <cstring>

using namespace std;

MyString::MyString() : string(nullptr), length(0) {}
//changed from dynamic to nullptr

MyString::MyString(const char* input) {
    length=strlen(input);
    string = new char [length +1];
    strcpy(string,input); // smile:) i really didn't want to copy char by char xD
}

MyString::MyString(const MyString &other){
    length= other.length;
    string = new char [length +1];
    strcpy(string,other.string);
}

MyString::~MyString (){
    delete [] string;
    cout<<"destructed MyString"<<endl;
}
//Assignment operator
MyString& MyString::operator=(const MyString &other) {
    if (this != &other) { 
        delete[] string;  
        length = other.length;
        string = new char[length + 1];
        strcpy(string, other.string);
    }
    return *this; //return reference to current object
}

char MyString::get(int i) const {
    if (!string) {  //check for nullptr
        throw runtime_error("String is null! Cannot modify.");
    }
    if (i < 0 || i >= static_cast<int>(length)) {
        throw out_of_range("Index out of bounds");
    }
    return string[i];
}

void MyString::set(int i, char c) {
    if (!string) {  //check for nullptr
        throw runtime_error("String is null! Cannot modify.");
    }
      if (i < 0 || i >= static_cast<int>(length)) {
        throw out_of_range("Index out of bounds");
    }
    string[i] = c; 
}

void MyString::set_new_string(const char* new_string){
    if (!new_string) {  //check for nullptr
        throw invalid_argument("Cannot set a null string!");
    }
    
    if (string) {  //also check for nullptr
        delete [] string;
    }

    length = strlen(new_string);
    string = new char [length + 1];
    strcpy(string, new_string);
}

void MyString::print() const{
    if (!string) {//check for nullptr
        cout << "(null string)" << endl;
        return;
    }
    cout<<string<<endl;
}

void MyString::read_line(){
    char buffer[1000];
    cin.getline(buffer, 1000);
    if (cin.fail()) {  //check if buffer was returned as nullptr (to avoid crash)
        throw runtime_error("Failed to read input!");
    }
    set_new_string(buffer);
}

// ops

MyString& MyString::operator+=(const MyString& other){
    if (!string && !other.string){
        return *this;
    } 
        size_t newLength= length + other.length;
        char* newString = new char [newLength +1];
        if (string){
            strcpy(newString,string);
        }
        else {
            newString[0]='\0';
        }
    
    strcat(newString,other.string);
    delete [] string;
    string = newString;
    length=newLength;
    return *this;
}
MyString& MyString::operator+=(const char* str){
    if (!str){
        throw std::invalid_argument("cannot append null str");
    }
    size_t strLength=strlen(str);
    size_t newLength= strLength + length;
    char* newString = new char [newLength + 1];
    if(string){
        strcpy(newString,string);
    }
    else {
        newString[0]='\0';
    }
    strcat(newString,str);
    delete [] string;
    string = newString;
    length = newLength;
    return *this;
}
MyString MyString::operator+(const MyString& other) const {
    /*if ( !string || !other.string){
        throw std::invalid_argument ("cant concatenate null string");
    }*/
    size_t newLength= length + other.length;
    char* newString = new char[newLength +1 ];
    strcpy(newString,string);
    strcat(newString,other.string);
    MyString result(newString);
    delete [] newString;
    return result;
}
MyString operator+(const char* str, const MyString& s) {
    if (!str|| !s.string){
        throw std::invalid_argument("cant concatenate null string");
    }
    size_t strLength=strlen(str);
    size_t newLength= strLength + s.length;
    char* newString = new char[newLength +1];
    strcpy(newString,str);
    strcat(newString,s.string);
    MyString result(newString);
    delete [] newString;
    return result;
}
bool MyString::operator==(const MyString& other)const {
    if (!string && !other.string) return true;
    if (!string || !other.string) return false;
    return strcmp(string, other.string) == 0; 
}
bool MyString::operator!=(const MyString& other) const{
    return !(*this== other);
}
bool MyString::operator<(const MyString& other) const{
    if (!string && !other.string) return false;
    if (!string) return true;
    if (!other.string) return false;
    return strcmp(string, other.string) < 0;
}
bool MyString::operator<=(const MyString& other)const {
    return *this < other || *this == other;
}
bool MyString::operator==(const char* str) const {
    if (!string && !str) return true;
    if (!string || !str) return false;
    return strcmp(string,str) == 0;
}
bool MyString::operator!=(const char* str) const{
    return !(*this == str); 
}
bool MyString::operator<(const char* str) const {
    if (!string && !str) return false;
    if (!string) return true;
    if (!str) return false;
    return strcmp(string,str) < 0;
}
bool MyString::operator<=(const char* str)const {
    return *this < str || *this == str;
}
bool operator==(const char* str, const MyString& s) {
    return s == str; 
}
bool operator!=(const char* str, const MyString& s) {
    return !(str == s);
}

bool operator<(const char* str, const MyString& s) {
    return strcmp(str, s.string) < 0;
}

bool operator<=(const char* str, const MyString& s) {
    return (str < s || str == s);
}
char& MyString::operator[](int i) {
    if(!string) throw std::runtime_error("cannot index null strings");
    if (i<0 || i> length) throw std::out_of_range("index is bigger than string size");
    return string[i];
}
std::ostream& operator<<(std::ostream& os, const MyString& s) {
    if (s.string) {
        os << s.string; 
    } else {
        os << "(null string)"; 
    }
    return os;
}
std::istream& operator>>(std::istream& is, MyString& s) {
    char buffer[1000]; 
    is.getline(buffer, 1000); 
    if (is.fail()) {
        throw std::runtime_error("failed to read input!"); 
    }
    s.set_new_string(buffer); 
    return is;
}
const char& MyString::operator[](int i) const {
    if(!string) throw std::runtime_error("cannot index null strings");
    if (i<0 || i >= length) throw std::out_of_range("index is bigger than string size");
    return string[i];
}
MyString MyString::operator+(const char* str) const {
    if (!str) {
        throw std::invalid_argument("cannot concatenate with null string");
    }
    
    size_t strLength = strlen(str);
    size_t newLength = length + strLength;
    char* newString = new char[newLength + 1];
    
    if (string) {
        strcpy(newString, string);
    } else {
        newString[0] = '\0';
    }
    
    strcat(newString, str);
    MyString result(newString);
    delete[] newString;
    return result;
}