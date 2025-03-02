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
    cout<<"destructed ahahahah"<<endl;
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