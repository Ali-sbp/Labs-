#ifndef OPTIMIZED_SHORTARRAY_HPP
#define OPTIMIZED_SHORTARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <iostream>

class OptimizedShortArray {
private:
    static constexpr size_t MAX_INLINE = 8; // adjust based on calculation
    
    //using union to store either a pointer to dynamic memory or an inline array
    union {
        struct {
            short* data;
            size_t capacity;
        } dynamic;
        
        short inline_data[MAX_INLINE];
    };
    
    size_t count;      //number of elems
    bool is_dynamic;   //storage type flag
    
    // Helper methods
    void allocate(size_t new_capacity);
    void deallocate();
    bool should_be_dynamic(size_t size) const { return size > MAX_INLINE; }

public:
    //cons & des
    OptimizedShortArray();
    explicit OptimizedShortArray(size_t size);
    OptimizedShortArray(size_t size, short value);
    OptimizedShortArray(const OptimizedShortArray& other);
    ~OptimizedShortArray();
    
    //assignment operator
    OptimizedShortArray& operator=(const OptimizedShortArray& other);
    
    //element access
    short& operator[](size_t index);
    const short& operator[](size_t index) const;
    
    //methods
    void push(short new_val);
    short pop();
    size_t size() const { return count; }
    void resize(size_t new_size, short fill_value = 0);
    
    //debug method
    void print_storage_info() const {
        if (is_dynamic) {
            std::cout << "Dynamic storage, capacity: " << dynamic.capacity << std::endl;
        } else {
            std::cout << "Inline storage, max capacity: " << MAX_INLINE << std::endl;
        }
    }
};

#endif // OPTIMIZED_SHORTARRAY_HPP