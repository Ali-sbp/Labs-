#include "barrel.hpp"
#include "rect.hpp"
#include "matrix.hpp"
#include "textwrapper.hpp"
#include "MyString.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

int main(){
    //rect
    {
    rect r1(1,2,3,4), r2(5,6,7,8);
        rect r3 = bounding_rect(r1, r2);
        print_rect(r3);

    rect r5(1,2,3,4); 
    r5.set_width(10);
    print_rect(r5); 
    }
    //barrel 
    {
    Barrel alchohol ( 100 , 96);
    Barrel water (100, 0.0);
    int iteration =0; 

    const double target_consentration= 50;

    while (alchohol.get_consentration()>target_consentration){

        double transfered_alch = alchohol.pour_out();

        water.receive(transfered_alch);

        transfered_alch = water.pour_out();
        alchohol.receive(transfered_alch);

        iteration ++;

    }

    cout << "Final result after "<< iteration << " : iterations"<<endl;
}
        //MyString
{
        MyString s1;
        MyString s2 = s1;
        //MyString s4 = s3;
}
        //textwrapper
        {
        const int linelength = 40;
        const int linenumber = 20;

        textwrapper wrapper(linelength, linenumber);
        wrapper.readinput();
        wrapper.wraptext();
        wrapper.printbubble();
    }

   
}

