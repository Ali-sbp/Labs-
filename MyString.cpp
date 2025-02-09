#include "MyString.hpp"
#include <iostream>
#include <cstring>

using namespace std;

MyString::MyString() : string(new char [1]{'\0'}), length (0) {}

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
    if (i < 0 || i >= static_cast<int>(length)) {
        throw out_of_range("Index out of bounds");
    }
    return string[i];
}

void MyString::set(int i, char c) {
      if (i < 0 || i >= static_cast<int>(length)) {
        throw out_of_range("Index out of bounds");
    }
    string[i] = c; 
}

void MyString::set_new_string(const char* new_string){
    delete [] string; 
    length= strlen(new_string);
    string = new char [length+1];
    strcpy(string,new_string);
}

void MyString::print() const{
    cout<<string<<endl;
}

void MyString::read_line(){
    char buffer[1000];
    cin.getline(buffer,1000);
    set_new_string(buffer); //smile :)
}