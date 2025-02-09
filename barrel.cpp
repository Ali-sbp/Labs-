//test branch ffs

#include "barrel.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Barrel::Barrel(double water, double alchohol) : totalvolume(water) , alchvolume(alchohol) {
    if(water<alchohol) {
        throw invalid_argument("error , alchohol volume cant be bigger than max vol");

    }
}

double Barrel::get_consentration() const {
    if (totalvolume==0) return 0.0;
    return (alchvolume / totalvolume) * 100; 
}

double Barrel::pour_out(){
    if (totalvolume < 1.0) {
        throw runtime_error("not enough volume of liquid");
    }
    double consentration = alchvolume / totalvolume;
    double poured_alch = consentration; 

    alchvolume -= poured_alch; 
    totalvolume -= 1; 
    
    return poured_alch;
}

void Barrel::receive(double alch_recieved) {

    alchvolume += alch_recieved; 
    totalvolume += 1.0;


}