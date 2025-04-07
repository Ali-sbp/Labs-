#include "../src/BitOptimizedShortArray.hpp"
#include "../src/ShortArray.hpp"
#include "../src/OptimizedShortArray.hpp"

void test_bit_optimized_array() {
    using namespace std;
    
    cout << "Size of BitOptimizedShortArray: " << sizeof(BitOptimizedShortArray) << " bytes\n";
    cout << "Size of ShortArray: " << sizeof(ShortArray) << " bytes\n";
    cout << "Size of OptimizedShortArray: " << sizeof(OptimizedShortArray) << " bytes\n";
    
    cout << "\n=== Small Array Test ===\n";
    BitOptimizedShortArray small(3, 42);
    small.print_storage_info();
    cout << "Elements: ";
    for (size_t i = 0; i < small.size(); ++i) {
        cout << small[i] << " ";
    }
    cout << endl;
    
    cout << "\n=== Push Test (Inline) ===\n";
    BitOptimizedShortArray growing;
    growing.print_storage_info();
    
    for (short i = 0; i < 5; ++i) {
        growing.push(i * 10);
        cout << "Added " << i*10 << ", size: " << growing.size() << ", ";
        growing.print_storage_info();
    }
    
    cout << "\n=== Transition to Dynamic Storage ===\n";
    for (short i = 5; i < 15; ++i) {
        growing.push(i * 10);
        cout << "Added " << i*10 << ", size: " << growing.size() << ", ";
        growing.print_storage_info();
    }
    
    cout << "\n=== Large Array Test ===\n";
    BitOptimizedShortArray large(20, 100);
    large.print_storage_info();
    cout << "First few elements: ";
    for (size_t i = 0; i < 5; ++i) {
        cout << large[i] << " ";
    }
    cout << "...\n";
    
    cout << "\n=== Resize Test ===\n";
    large.resize(4, 0);
    cout << "After resizing to 4: ";
    large.print_storage_info();
    cout << "Elements: ";
    for (size_t i = 0; i < large.size(); ++i) {
        cout << large[i] << " ";
    }
    cout << endl;
    
    cout << "\n=== Copy Test ===\n";
    BitOptimizedShortArray copy1(small);
    BitOptimizedShortArray copy2(large);
    
    cout << "copy1 (from small): ";
    copy1.print_storage_info();
    
    cout << "copy2 (from large): ";
    copy2.print_storage_info();
}

int main() {
   
    
    test_bit_optimized_array();
    
    return 0;
}