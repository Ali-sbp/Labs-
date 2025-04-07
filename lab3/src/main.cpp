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
#include "ShortArray.hpp"

using namespace std;

int main(){
    {
        MyString s1("AAA"), s2;
        s2 = s1;
        s1 = "CCC";
        s2 = MyString("tmp");
        s1 = s1;
    }
    {
        Matrix m1(10), m2(10, 2,1);
        m1 = m2;
        m2 = Matrix(3, 4, 1.0);
        m1 = m1;
    } 
    {
        Matrix m1(4), m2(4, 4, 1);
        m2 += m1;
        m2 -= m1 += m1;
        m1 *= 2.0;
        m2 /= 3.0;
    }
    {
        Matrix m1(4), m2(4, 4, 1);
        Matrix m3 = (m1 + m2) * m1 * 4 / 2 - m2;
    } 
    {
        MyString s1("abc"), s2("def"), s3;
        s1 += s2 += "111";
        s2 += "222" + s1 + "333";
        s3 += s3;
    }
    {
        MyString s1("abc"), s2("ab"), s3 = s1;
        assert(s2 < s1);
        assert(s1 == s3);
        assert(s1 != s2);
        assert(s1 <= s3);
        assert("ab" == s2);
        assert("aba" < s1);
        assert("aba" <= s3);
    }
    {
        MyString s1("abc");
        s1[0] = s1[1] = 'd';
       
    }

    //ShortArray test:
    {
        
    }
   return 0;
}

