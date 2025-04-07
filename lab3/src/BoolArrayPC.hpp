#ifndef BOOLARRAY_HPP
#define BOOLARRAY_HPP

#include <cstddef>
#include <cmath>
#include <iostream>

class BoolProxy;  //forward declaration

class BoolArray {
private:
    unsigned char* data;   //array of bytes to store bits
    size_t num_bits;       //number of boolean values (bits)
    
    //helper
    size_t bytes_needed(size_t bits) const {
        return (bits + 7) / 8;  //ceil(bits / 8)
    }
    
    //get bit position and byte index
    void get_position(size_t bit_index, size_t& byte_index, unsigned char& bit_mask) const {
        byte_index = bit_index / 8;
        bit_mask = 1 << (bit_index % 8);
    }
    
public:
    //cons
    BoolArray();
    explicit BoolArray(size_t size, bool default_value = false);
     //copy constructor
    BoolArray(const BoolArray& other); 
    ~BoolArray();
    
    //assignment op
    BoolArray& operator=(const BoolArray& other);
    
    //proxy class to handle bit references and assignment
    friend class BoolProxy;
    
    //element access - returns a proxy object for assignment operations
    BoolProxy operator[](size_t index);
    
    //const element access - returns boolean value directly
    bool operator[](size_t index) const;
    
    //size method
    size_t size() const { return num_bits; }
    
    //resize method
    void resize(size_t new_size, bool fill_value = false);
};

//proxy class for representing a reference to a bit
class BoolProxy {
private:
    BoolArray& array;
    size_t index;
    
public:
    BoolProxy(BoolArray& arr, size_t idx) : array(arr), index(idx) {}
    
    //implicit conversion to bool
    operator bool() const {
        size_t byte_index;
        unsigned char bit_mask;
        array.get_position(index, byte_index, bit_mask);
        return (array.data[byte_index] & bit_mask) != 0;
    }
    
    //assignment operator
    BoolProxy& operator=(bool value) {
        size_t byte_index;
        unsigned char bit_mask;
        array.get_position(index, byte_index, bit_mask);
        
        if (value) {
            array.data[byte_index] |= bit_mask;  // Set bit
        } else {
            array.data[byte_index] &= ~bit_mask; // Clear bit
        }
        
        return *this;
    }
    
    //assignment from another proxy
    BoolProxy& operator=(const BoolProxy& other) {
        return *this = bool(other);
    }
    
    //support for boolean operations
    bool operator&&(bool other) const { return bool(*this) && other; }
    bool operator||(bool other) const { return bool(*this) || other; }
    bool operator!() const { return !bool(*this); }
    bool operator!=(bool other) const { return bool(*this) != other; }
};

// To enable operations like: !array[i] && array[j]
inline std::ostream& operator<<(std::ostream& os, const BoolProxy& proxy) {
    os << bool(proxy);
    return os;
}

#endif // BOOLARRAY_HPP