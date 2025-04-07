#include "OptimizedShortArray.hpp"
#include <stdexcept>


OptimizedShortArray::OptimizedShortArray() : count(0), is_dynamic(false) {
   
}


OptimizedShortArray::OptimizedShortArray(size_t size) : count(0), is_dynamic(false) {
    resize(size);
}


OptimizedShortArray::OptimizedShortArray(size_t size, short value) : count(0), is_dynamic(false) {
    resize(size, value);
}

//copy cons
OptimizedShortArray::OptimizedShortArray(const OptimizedShortArray& other) : count(other.count), is_dynamic(other.is_dynamic) {
    if (other.is_dynamic) {
        //copy dynamic
        dynamic.capacity = other.count;
        dynamic.data = new short[dynamic.capacity];
        for (size_t i = 0; i < count; i++) {
            dynamic.data[i] = other.dynamic.data[i];
        }
    } else {
        //copy inline
        for (size_t i = 0; i < count; i++) {
            inline_data[i] = other.inline_data[i];
        }
    }
}

//des
OptimizedShortArray::~OptimizedShortArray() {
    if (is_dynamic) {
        deallocate();
    }
}

//assignment op
OptimizedShortArray& OptimizedShortArray::operator=(const OptimizedShortArray& other) {
    if (this != &other) {
        //heap sweep
        if (is_dynamic) {
            deallocate();
        }
        
        count = other.count;
        is_dynamic = other.is_dynamic;
        
        if (other.is_dynamic) {
            //copy dynamic
            dynamic.capacity = other.count;
            dynamic.data = new short[dynamic.capacity];
            for (size_t i = 0; i < count; i++) {
                dynamic.data[i] = other.dynamic.data[i];
            }
        } else {
            //Copy inline
            for (size_t i = 0; i < count; i++) {
                inline_data[i] = other.inline_data[i];
            }
        }
    }
    return *this;
}


short& OptimizedShortArray::operator[](size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (is_dynamic) {
        return dynamic.data[index];
    } else {
        return inline_data[index];
    }
}

//const version of index method
const short& OptimizedShortArray::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (is_dynamic) {
        return dynamic.data[index];
    } else {
        return inline_data[index];
    }
}

//
void OptimizedShortArray::allocate(size_t new_capacity) {
    if (new_capacity <= MAX_INLINE) {
        //use inline storage instead
        if (is_dynamic) {
            //convert from dynamic to inline
            short* old_data = dynamic.data;
            // only copy what will fit in inline storage
            size_t elements_to_copy = (count <= MAX_INLINE) ? count : MAX_INLINE;
            for (size_t i = 0; i < elements_to_copy; i++) {
                inline_data[i] = old_data[i];
            }
            delete[] old_data;
            is_dynamic = false;
            //if we couldn't copy all elements, adjust count
            if (count > MAX_INLINE) {
                count = MAX_INLINE;
            }
        }
    } else {
        //use dynamic storage
        short* new_data = new short[new_capacity];
        
        //copy existing data
        if (is_dynamic) {
            for (size_t i = 0; i < count; i++) {
                new_data[i] = dynamic.data[i];
            }
            delete[] dynamic.data;
        } else {
            for (size_t i = 0; i < count; i++) {
                new_data[i] = inline_data[i];
            }
            is_dynamic = true;
        }
        
        dynamic.data = new_data;
        dynamic.capacity = new_capacity;
    }
}

//
void OptimizedShortArray::deallocate() {
    if (is_dynamic) {
        delete[] dynamic.data;
        dynamic.data = nullptr;
        dynamic.capacity = 0;
    }
    count = 0;
    is_dynamic = false;
}

//
void OptimizedShortArray::push(short new_val) {
    if (is_dynamic) {
        if (count == dynamic.capacity) {
            size_t new_capacity = dynamic.capacity * 2;
            allocate(new_capacity);
        }
        dynamic.data[count++] = new_val;
    } else {
        if (count == MAX_INLINE) {
            allocate(MAX_INLINE * 2);
            dynamic.data[count++] = new_val;
        } else {
            inline_data[count++] = new_val;
        }
    }
}


short OptimizedShortArray::pop() {
    if (count == 0) {
        throw std::runtime_error("Cannot pop from empty array");
    }
    
    count--;
    if (is_dynamic) {
        return dynamic.data[count];
    } else {
        return inline_data[count];
    }
}


void OptimizedShortArray::resize(size_t new_size, short fill_value) {
    if (new_size == count) {
        return;
    }
    
    if (new_size == 0) {
        if (is_dynamic) {
            deallocate();
        }
        count = 0;
        return;
    }
    
    bool should_be_dyn = should_be_dynamic(new_size);
    
    //if we're shrinking and the storage type should change (dynamic to inline)
    if (new_size < count && is_dynamic && !should_be_dyn) {
        //convert
        allocate(new_size);
        for (size_t i = count; i < new_size; i++) { //just in case, i know not needed 
            inline_data[i] = fill_value;
        }
        return;
    }
    // if shrinking and staying in the same storage type
    else if (new_size < count && should_be_dyn == is_dynamic) {
        count = new_size;
        return;
    }
    
    // If growing and need to switch storage type or increase capacity
    if (should_be_dyn && (!is_dynamic || new_size > dynamic.capacity)) {
        allocate(new_size);
    }
    
    //fill new elements
    size_t old_count = count;
    count = new_size;
    
    for (size_t i = old_count; i < new_size; i++) {
        if (is_dynamic) {
            dynamic.data[i] = fill_value;
        } else {
            inline_data[i] = fill_value;
        }
    }
}