#include "BitOptimizedShortArray.hpp"
#include <stdexcept>


BitOptimizedShortArray::BitOptimizedShortArray() : count(0) {
    set_pointer(nullptr);
    set_dynamic(false);
}

BitOptimizedShortArray::BitOptimizedShortArray(size_t size) : count(0) {
    set_pointer(nullptr);
    set_dynamic(false);
    resize(size);
}

BitOptimizedShortArray::BitOptimizedShortArray(size_t size, short value) : count(0) {
    set_pointer(nullptr);
    set_dynamic(false);
    resize(size, value);
}

//copy cons
BitOptimizedShortArray::BitOptimizedShortArray(const BitOptimizedShortArray& other) : count(other.count) {
    if (other.is_dynamic()) {
        //copy dynamic
        set_dynamic(true);
        dynamic.capacity = other.dynamic.capacity;
        set_pointer(new short[dynamic.capacity]);
        
        for (size_t i = 0; i < count; i++) {
            get_pointer()[i] = other.get_pointer()[i];
        }
    } else {
        //copy inline 
        set_dynamic(false);
        set_pointer(nullptr);
        for (size_t i = 0; i < count; i++) {
            inline_storage.inline_data[i] = other.inline_storage.inline_data[i];
        }
    }
}

BitOptimizedShortArray::~BitOptimizedShortArray() {
    if (is_dynamic()) {
        deallocate();
    }
}

//assign op
BitOptimizedShortArray& BitOptimizedShortArray::operator=(const BitOptimizedShortArray& other) {
    if (this != &other) {
        //heap sweeeeeper :D
        if (is_dynamic()) {
            deallocate();
        }
        
        count = other.count;
        
        if (other.is_dynamic()) {
            //copy dynamic array
            set_dynamic(true);
            dynamic.capacity = other.dynamic.capacity;
            set_pointer(new short[dynamic.capacity]);
            
            for (size_t i = 0; i < count; i++) {
                get_pointer()[i] = other.get_pointer()[i];
            }
        } else {
            //copy inline array
            set_dynamic(false);
            set_pointer(nullptr);
            for (size_t i = 0; i < count; i++) {
                inline_storage.inline_data[i] = other.inline_storage.inline_data[i];
            }
        }
    }
    return *this;
}

//index
short& BitOptimizedShortArray::operator[](size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (is_dynamic()) {
        return get_pointer()[index];
    } else {
        return inline_storage.inline_data[index];
    }
}

//const version of index
const short& BitOptimizedShortArray::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (is_dynamic()) {
        return get_pointer()[index];
    } else {
        return inline_storage.inline_data[index];
    }
}

//
void BitOptimizedShortArray::allocate(size_t new_capacity) {
    if (new_capacity <= MAX_INLINE) {
        //inline
        if (is_dynamic()) {
            // convert from dynamic to inline
            short* old_ptr = get_pointer();
            
            //only copy what will fit in inline storage
            size_t elements_to_copy = (count <= MAX_INLINE) ? count : MAX_INLINE;
            for (size_t i = 0; i < elements_to_copy; i++) {
                inline_storage.inline_data[i] = old_ptr[i];
            }
            
            delete[] old_ptr;
            set_dynamic(false);
            set_pointer(nullptr);
            
            //if we couldn't copy all elements, adjust count
            if (count > MAX_INLINE) {
                count = MAX_INLINE;
            }
        }
    } else {
        //dynamic storage
        short* new_ptr = new short[new_capacity];
        
        //copy existing data
        if (is_dynamic()) {
            short* old_ptr = get_pointer();
            for (size_t i = 0; i < count; i++) {
                new_ptr[i] = old_ptr[i];
            }
            delete[] old_ptr;
        } else {
            for (size_t i = 0; i < count; i++) {
                new_ptr[i] = inline_storage.inline_data[i];
            }
        }
        
        set_dynamic(true);
        set_pointer(new_ptr);
        dynamic.capacity = new_capacity;
    }
}

//
void BitOptimizedShortArray::deallocate() {
    if (is_dynamic()) {
        delete[] get_pointer();
        set_pointer(nullptr);
        dynamic.capacity = 0;
    }
    count = 0;
    set_dynamic(false);
}

//push
void BitOptimizedShortArray::push(short new_val) {
    if (is_dynamic()) {
        //dynamic storage
        if (count == dynamic.capacity) {
            size_t new_capacity = dynamic.capacity * 2;
            allocate(new_capacity);
        }
        get_pointer()[count++] = new_val;
    } else {
        //inline storage
        if (count == MAX_INLINE) {
            //switch to dynamic storage
            allocate(MAX_INLINE * 2);
            get_pointer()[count++] = new_val;
        } else {
            inline_storage.inline_data[count++] = new_val;
        }
    }
}

//remove and return element from the end
short BitOptimizedShortArray::pop() {
    if (count == 0) {
        throw std::runtime_error("Cannot pop from empty array");
    }
    
    count--;
    if (is_dynamic()) {
        return get_pointer()[count];
    } else {
        return inline_storage.inline_data[count];
    }
}

//resize the array
void BitOptimizedShortArray::resize(size_t new_size, short fill_value) {
    //if same size, do nothing
    if (new_size == count) {
        return;
    }
    
    //if new size is 0, deallocate
    if (new_size == 0) {
        if (is_dynamic()) {
            deallocate();
        }
        count = 0;
        return;
    }
    
    bool should_be_dyn = should_be_dynamic(new_size);
    
    //if shrinking and storage type should change (dynamic to inline)
    if (new_size < count && is_dynamic() && !should_be_dyn) {
        //convert from dynamic to inline
        allocate(new_size);
        return;
    }
    //if shrinking and staying in the same storage type
    else if (new_size < count && should_be_dyn == is_dynamic()) {
        count = new_size;
        return;
    }
    
    //if growing and need to switch storage type or increase capacity
    if (should_be_dyn && (!is_dynamic() || new_size > dynamic.capacity)) {
        allocate(new_size);
    }
    
    //fill new elements
    size_t old_count = count;
    count = new_size;
    
    for (size_t i = old_count; i < new_size; i++) {
        if (is_dynamic()) {
            get_pointer()[i] = fill_value;
        } else {
            inline_storage.inline_data[i] = fill_value;
        }
    }
}