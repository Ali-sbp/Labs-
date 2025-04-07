#ifndef BIT_OPTIMIZED_SHORTARRAY_HPP
#define BIT_OPTIMIZED_SHORTARRAY_HPP

#include <cstddef>
#include <cstdint> // for uintptr_t 
#include <stdexcept>
#include <iostream>

class BitOptimizedShortArray {
private:
    
    union {
        struct {
            short* ptr;      
            size_t capacity; 
        } dynamic;
        
        struct {
            uintptr_t ptr_and_flag : sizeof(uintptr_t) * 8;
            
            // inline array directly in the object
            short inline_data[sizeof(size_t) / sizeof(short)];
        } inline_storage;
    };
    
    size_t count;  
    
    //helpers
    static constexpr size_t MAX_INLINE = sizeof(size_t) / sizeof(short); //constexpr for stability (i read on it a bit)
    bool is_dynamic() const { return (inline_storage.ptr_and_flag & 1) == 0; }
    void set_dynamic(bool dyn) {
        if (dyn) {
            inline_storage.ptr_and_flag &= ~(uintptr_t)1; //clear flag bit = dynamic
        } else {
            inline_storage.ptr_and_flag |= 1;  //set flag bit = inline
        }
    }
    short* get_pointer() const {
        return (short*)(inline_storage.ptr_and_flag & ~(uintptr_t)1);
    }
    void set_pointer(short* ptr) {
        //save the flag bit when setting the pointer
        inline_storage.ptr_and_flag = (uintptr_t)ptr | (inline_storage.ptr_and_flag & 1);
    }
    bool should_be_dynamic(size_t size) const { return size > MAX_INLINE; }
    
public:
    //const & decons
    BitOptimizedShortArray();
    explicit BitOptimizedShortArray(size_t size);
    BitOptimizedShortArray(size_t size, short value);
    BitOptimizedShortArray(const BitOptimizedShortArray& other);
    ~BitOptimizedShortArray();
    
    //assign op
    BitOptimizedShortArray& operator=(const BitOptimizedShortArray& other);
    
    //index
    short& operator[](size_t index);
    const short& operator[](size_t index) const;
    
    //methods
    void push(short new_val);
    short pop();
    size_t size() const { return count; }
    void resize(size_t new_size, short fill_value = 0);
    
    
    void allocate(size_t new_capacity);
    void deallocate();
    
    //debug info method
    void print_storage_info() const {
        if (is_dynamic()) {
            std::cout << "Dynamic storage, capacity: " << dynamic.capacity << std::endl;
        } else {
            std::cout << "Inline storage, max capacity: " << MAX_INLINE << std::endl;
        }
    }
};

#endif // BIT_OPTIMIZED_SHORTARRAY_HPP