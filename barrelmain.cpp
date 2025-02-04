#include "barrel.hpp"
#include "barrel.cpp"

#include <iostream>

using namespace std;

int main () {
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

    return 0;
}