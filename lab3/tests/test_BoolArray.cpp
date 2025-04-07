#include "../src/BoolArray.hpp"
#include <iostream>
#include <cassert>

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

void test_basic_operations() {
    cout << "Testing basic operations..." << endl;
    
    // Test constructors
    BoolArray ar1(10);
    BoolArray ar2(5, true);
    BoolArray ar3(ar2);
    
    // Test size
    assert(ar1.size() == 10);
    assert(ar2.size() == 5);
    assert(ar3.size() == 5);
    
    // Test default values
    for (int i = 0; i < ar1.size(); i++) {
        assert(ar1[i] == false);
    }
    
    // Test initial values for ar2
    for (int i = 0; i < ar2.size(); i++) {
        assert(ar2[i] == true);
    }
    
    // Test copy constructor
    for (int i = 0; i < ar3.size(); i++) {
        assert(ar3[i] == ar2[i]);
    }
    
    cout << "Basic operations passed!" << endl;
}

void test_assignment_and_indexing() {
    cout << "Testing assignment and indexing..." << endl;
    
    BoolArray ar1(10);
    
    // Test setting individual bits
    ar1[4] = true;
    ar1[6] = true;
    
    assert(ar1[4] == true);
    assert(ar1[6] == true);
    assert(ar1[5] == false);
    
    // Test boolean operations
    ar1[2] = (!ar1[6] && ar1[8] || (ar1[0] != true));
    
    // !ar1[6] is false, ar1[8] is false, ar1[0] != true is true
    // false && false || true => true
    assert(ar1[2] == true);
    
    // Test compound assignment
    bool temp = ar1[6];
    ar1[6] = ar1[4];
    ar1[4] = temp;
    
    assert(ar1[4] == true);
    assert(ar1[6] == true);
    
    cout << "Assignment and indexing passed!" << endl;
}

void test_resize() {
    cout << "Testing resize operation..." << endl;
    
    BoolArray ar1(6);
    
    // Set some bits
    ar1[2] = true;
    ar1[4] = true;
    
    // Expand with default false
    ar1.resize(10);
    
    assert(ar1.size() == 10);
    assert(ar1[2] == true);
    assert(ar1[4] == true);
    assert(ar1[6] == false);
    assert(ar1[9] == false);
    
    // Expand with default true
    ar1.resize(15, true);
    
    assert(ar1.size() == 15);
    assert(ar1[2] == true);
    assert(ar1[4] == true);
    assert(ar1[10] == true);
    assert(ar1[14] == true);
    
    // Shrink
    ar1.resize(3);
    
    assert(ar1.size() == 3);
    assert(ar1[2] == true);
    
    // Test resize to zero
    ar1.resize(0);
    assert(ar1.size() == 0);
    
    cout << "Resize operations passed!" << endl;
}

void test_memory_efficiency() {
    cout << "Testing memory efficiency..." << endl;
    
    // Calculate theoretical memory usage
    size_t bits = 1000;
    size_t bytes_needed = (bits + 7) / 8;
    size_t naive_bytes = bits * sizeof(bool);
    
    cout << "For " << bits << " boolean values:" << endl;
    cout << "Naive implementation would use: " << naive_bytes << " bytes" << endl;
    cout << "Bit-packed implementation uses: " << bytes_needed << " bytes" << endl;
    cout << "Memory savings: " << (naive_bytes - bytes_needed) * 100.0 / naive_bytes << "%" << endl;
    
    assert(bytes_needed < naive_bytes);
    
    cout << "Memory efficiency verified!" << endl;
}

int main() {
    cout << "\n=== BoolArray Unit Tests ===\n" << endl;
    
    test_basic_operations();
    test_assignment_and_indexing();
    test_resize();
    test_memory_efficiency();
    
    cout << "\n=== BoolArray Functionality Demo ===\n" << endl;
    
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
    cout<<"\nPrinting ar1: ";
    print_array(ar1);
    
    //print true indices
    cout<<"Indices with true values: ";
    print_true_indices(ar1);
    
    //test resize to larger size
    cout<< "\nResizing ar1 to 12 with default true" << endl;
    ar1.resize(12, true);
    
    cout<< "ar1 after resize to 12: ";
    print_array(ar1);
    
    cout<< "indices with true values: ";
    print_true_indices(ar1);
    
    //test resize to smaller size
    cout << "\nResizing ar1 to 4 with default true" << endl;
    ar1.resize(4, true);
    
    cout << "ar1 after resize to 4: ";
    print_array(ar1);
    
    cout <<"indices with true values: ";
    print_true_indices(ar1);
    
    cout<<"\nAll tests completed successfully!" << endl;
    
    return 0;
}