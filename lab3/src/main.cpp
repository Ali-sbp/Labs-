#include "barrel.hpp"
#include "rect.hpp"
#include "matrix.hpp"
#include "textwrapper.hpp"
#include "MyString.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <cassert>


using namespace std;

int main(){
    Matrix m1(10);
    Matrix m2(10,2,1);
    m1=m2;
    m2=Matrix(4,4,5);
    m1=m1;
    m1.print();
    m2.print();
    
   return 0;
}

