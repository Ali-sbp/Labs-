#include "textwrapper.hpp"
#include <cstring>
#include <iostream>


using namespace std;

textwrapper::textwrapper(int linelength, int linenumber) : linelength(linelength) , linenumber(linenumber), usedlines(0) {
    lines = new char*[linenumber];
    for (int i=0;i<linenumber; i++){
        lines[i]= new char [linelength +1];
    }
}

textwrapper::~textwrapper(){
    for (int i=0; i<linenumber ; i++){
        delete [] lines[i];
    }
    delete [] lines;
}

void textwrapper::readinput(){
    cout <<"enter text"<<endl; 
    cin.getline(input,800);

}

void textwrapper::wraptext(){
    int inputlength=strlen(input);
    int start = 0;
    usedlines = 0;
    while (start < inputlength && usedlines < linenumber) {
        int end = start + linelength;

        if (end < inputlength) {
            int spacePos = end;
            while (spacePos > start && input[spacePos] != ' ') {
                spacePos--;
            }
            if (spacePos > start) {
                end = spacePos;
            }
        }

        strncpy(lines[usedlines], &input[start], end - start);
        lines[usedlines][end - start] = '\0';

        start = end;
        while (start < inputlength && input[start] == ' ') {
            start++;
        }
        
        usedlines++;
    }
}

void textwrapper::printbubble(){
    int bubbleWidth = 0;
    for (int i = 0; i < usedlines; i++) {
        int len = strlen(lines[i]);
        if (len > bubbleWidth) {
            bubbleWidth = len;
        }
    }
    bubbleWidth = std::min(bubbleWidth, linelength);

    std::cout << " ";
    for (int i = 0; i < bubbleWidth + 2; i++) std::cout << "_";
    std::cout << std::endl;

    for (int i = 0; i < usedlines; i++) {
        std::cout << "/ " << lines[i];
        for (int j = strlen(lines[i]); j < bubbleWidth; j++) std::cout << " ";
        std::cout << " \\" << std::endl;
    }

    std::cout << "\\";
    for (int i = 0; i < bubbleWidth + 2; i++) std::cout << "_";
    std::cout << "/" << std::endl;
}


/*int main () {
    const int linelength = 40;
    const int linenumber = 20;

    textwrapper wrapper(linelength, linenumber);
    wrapper.readinput();
    wrapper.wraptext();
    wrapper.printbubble();
}*/