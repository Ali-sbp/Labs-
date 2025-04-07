#ifndef BOOLARRAY_HPP
#define BOOLARRAY_HPP

#include <cstddef>
#include <iostream>

class BoolArray {
private:
    unsigned char* data;    //array of bytes to store bits
    size_t num_bits;        //number of boolean values (bits)
    
    //helper methods
    size_t bytes_needed(size_t bits) const {
        return (bits + 7) / 8;  //ceil(bits / 8)
    }
    
    //BitReference inner class to handle bit access and modification 
    /*
    */

    class BitReference {
    public:
        BoolArray& array;
        size_t index;
    
    public:
        BitReference(BoolArray& arr, size_t idx) : array(arr), index(idx) {}
        
        //conversion to bool
        operator bool() const {
            size_t byte_index = index / 8;
            unsigned char bit_mask = 1 << (index % 8);
            return (array.data[byte_index] & bit_mask) != 0;
        }
        
        //assignment operator
        BitReference& operator=(bool value) {
            size_t byte_index = index / 8;
            unsigned char bit_mask = 1 << (index % 8);
            
            if (value) {
                array.data[byte_index] |= bit_mask;  //set bit
            } else {
                array.data[byte_index] &= ~bit_mask; //clear bit
            }
            
            return *this;
        }
        
        //assignment from another BitReference
        BitReference& operator=(const BitReference& other) {
            return *this = bool(other);
        }
    };

    //declare operator<< as a friend function
    friend std::ostream& operator<<(std::ostream& os, const BoolArray::BitReference& ref);
    
public:
    //constructors and destructor
    BoolArray();
    explicit BoolArray(size_t size, bool default_value = false);
    BoolArray(const BoolArray& other);
    ~BoolArray();
    
    //assignment operator
    BoolArray& operator=(const BoolArray& other);
    
    //element access
    BitReference operator[](size_t index);
    bool operator[](size_t index) const;
    
    //size method
    size_t size() const { return num_bits; }
    
    //resize method
    void resize(size_t new_size, bool fill_value = false);
    
    //debug helper
    void print_bits() const;
};

//enable ostream output for BitReference
inline std::ostream& operator<<(std::ostream& os, const BoolArray::BitReference& ref) {
    os << bool(ref);
    return os;
}

#endif // BOOLARRAY_HPP