#include <iostream>
#include "../src/ShortArray.hpp"
using namespace std;
int main() {

    ShortArray arr1;
    cout << "Initial size of arr1: " << arr1.size() << endl;
    
    arr1.push(10);
    arr1.push(20);
    arr1.push(30);
    
    cout << "After pushing 3 elements, size: " << arr1.size() << endl;
    cout << "Elements: ";
    for (size_t i = 0; i < arr1.size(); ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    ShortArray arr2(5);
    cout << "Initial size of arr2: " << arr2.size() << endl;
    cout << "Elements of arr2 (default): ";
    for (size_t i = 0; i < arr2.size(); ++i) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    ShortArray arr3(4, 42);
    cout << "Initial size of arr3: " << arr3.size() << endl;
    cout << "Elements of arr3 (filled with 42): ";
    for (size_t i = 0; i < arr3.size(); ++i) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    
    arr1.resize(5, 99);
    cout << "After resizing arr1 to 5, size: " << arr1.size() << endl;
    cout << "Elements of arr1: ";
    for (size_t i = 0; i < arr1.size(); ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    short val = arr1.pop();
    cout << "Popped value from arr1: " << val << endl;
    cout << "After pop, size: " << arr1.size() << endl;
    
    ShortArray arr4 = arr3;
    cout << "arr4 (copy of arr3) elements: ";
    for (size_t i = 0; i < arr4.size(); ++i) {
        cout << arr4[i] << " ";
    }
    cout << endl;
    
    arr1 = arr4;
    cout << "arr1 (after assignment from arr4) elements: ";
    for (size_t i = 0; i < arr1.size(); ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    return 0;
 }
 
    
 