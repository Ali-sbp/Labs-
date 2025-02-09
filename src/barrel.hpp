#ifndef BARREL_HPP
#define BARREL_HPP

#include <iostream>

class Barrel {
    private:
    double totalvolume;
    double alchvolume;
    public:
    Barrel (double a , double b); //: totalvolume(a) , alchvolume(b) {} >> moved to cpp file


    double get_consentration() const ;

    // iteration out
    double pour_out();

    // 
    void receive(double alch_received);
};

#endif