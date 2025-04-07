#ifndef TEXTWRAPPER_HPP
#define TEXTWRAPPER_HPP

#include <iostream>
#include <cstring>

class textwrapper
{
private:
    char** lines;
    char input [800];
    int usedlines;
    int linelength;
    int linenumber;

public:
    textwrapper(int linelength, int linenumber);
    ~textwrapper();
    void readinput();
    void wraptext();
    void printbubble();
};



#endif //TEXTWRAPPER