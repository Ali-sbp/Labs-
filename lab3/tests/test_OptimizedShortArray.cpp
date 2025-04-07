#include <iostream>
#include "../src/OptimizedShortArray.hpp"
#include "../src/ShortArray.hpp"
using namespace std;
void test_optimized_array() {
    using namespace std;
    
    cout << "Size of OptimizedShortArray: " << sizeof(OptimizedShortArray) << " bytes\n";
    cout << "Size of original ShortArray: " << sizeof(ShortArray) << " bytes\n";
    
    cout << "\n=== Small Array Test ===\n";
    OptimizedShortArray small(3, 42);
    small.print_storage_info();
    cout << "Elements: ";
    for (size_t i = 0; i < small.size(); ++i) {
        cout << small[i] << " ";
    }
    cout << endl;
    
    cout << "\n=== Push Test (Inline) ===\n";
    OptimizedShortArray growing;
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
    OptimizedShortArray large(20, 100);
    large.print_storage_info();
    cout << "First few elements: ";
    for (size_t i = 0; i < 5; ++i) {
        cout << large[i] << " ";
    }
    cout << "...\n";
    
    cout << "\n=== Resize Test ===\n";
    large.resize(5, 0);
    cout << "After resizing to 5: ";
    large.print_storage_info();
    
    cout << "\n=== Copy Test ===\n";
    OptimizedShortArray copy1(small);
    OptimizedShortArray copy2(large);
    
    cout << "copy1 (from small): ";
    copy1.print_storage_info();
    
    cout << "copy2 (from large): ";
    copy2.print_storage_info();
    
    cout << "\n=== Assignment Test ===\n";
    OptimizedShortArray assign1;
    assign1 = small;
    
    OptimizedShortArray assign2;
    assign2 = large;
    
    cout << "assign1 (from small): ";
    assign1.print_storage_info();
    
    cout << "assign2 (from large): ";
    assign2.print_storage_info();
}
int main (){
    cout << "size of original ShortArray: " << sizeof(ShortArray) << " bytes\n";
    cout << "size of short*: " << sizeof(short*) << " bytes\n";
    cout << "size of size_t: " << sizeof(size_t) << " bytes\n";
    
    //max that can fit
    size_t array_struct_size = sizeof(short*) + 2 * sizeof(size_t);
    size_t max_inline_shorts = array_struct_size / sizeof(short);
    
    cout << "We can fit " << max_inline_shorts << " shorts inline\n";
    test_optimized_array();
    return 0;
}