#include "../src/BoolArrayPC.hpp"
#include <iostream>

using namespace std;

void print_array(const BoolArray& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << arr[i];
    }
    cout << "]\n";
}

void print_true_indices(const BoolArray& arr) {
    cout << "[";
    for (int i = 0, printed = 0; i < arr.size(); ++i) {
        if (arr[i]) {
            if (printed++ > 0) cout << ", ";
            cout << i;
        }
    }
    cout << "]\n";
}

int main() {
    cout << "\n=== Testing BoolArray ===\n" << endl;
    
    //create array with default values
    cout << "Creating array ar1 with 10 false values" << endl;
    BoolArray ar1(10);
    
    //create array with true values
    cout << "Creating array ar2 with 5 true values" << endl;
    BoolArray ar2(5, true);
    
    //create a copy
    cout << "Creating array ar3 as a copy of ar2" << endl;
    BoolArray ar3(ar2);
    
    //set values
    cout << "\nSetting ar1[4] and ar1[6] to true" << endl;
    ar1[4] = ar1[6] = true;
    
    //perform boolean operations
    cout << "Setting ar1[2] = (!ar1[6] && ar1[8] || (ar1[0] != true))" << endl;
    ar1[2] = (!ar1[6] && ar1[8] || (ar1[0] != true));
    
    //print array
    cout << "\nPrinting ar1: ";
    print_array(ar1);
    
    //print true indices
    cout << "Indices with true values: ";
    print_true_indices(ar1);
    
    //test resize to larger size
    cout << "\nResizing ar1 to 12 with default true" << endl;
    ar1.resize(12, true);
    
    cout << "ar1 after resize to 12: ";
    print_array(ar1);
    
    cout << "Indices with true values: ";
    print_true_indices(ar1);
    
    //test resize to smaller size
    cout << "\nResizing ar1 to 4 with default true" << endl;
    ar1.resize(4, true);
    
    cout << "ar1 after resize to 4: ";
    print_array(ar1);
    
    cout << "Indices with true values: ";
    print_true_indices(ar1);
    
    //~~> test memory efficiency
    cout << "\n=== Memory Efficiency Test ===\n" << endl;
    
    //create a large array
    cout << "Creating an array of 1000 booleans" << endl;
    BoolArray large_array(1000);
    
    //calculate memory usage
    size_t naive_size = 1000 * sizeof(bool);
    size_t actual_bytes = (1000 + 7) / 8;
    
    cout << "Naive implementation (1000 booleans): " << naive_size << " bytes" << endl;
    cout << "Our implementation (1000 booleans): ~" << actual_bytes << " bytes" << endl;
    cout << "Memory saving: ~" << (naive_size - actual_bytes) * 100.0 / naive_size << "%" << endl;
    
    return 0;
}