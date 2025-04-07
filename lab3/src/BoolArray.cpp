#include "BoolArray.hpp"
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include <iostream>


BoolArray::BoolArray() : data(nullptr), num_bits(0) {}

//size constructor
BoolArray::BoolArray(size_t size, bool default_value) : num_bits(size) {
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    //allocate memory ~~> each byte holds 8 bits
    size_t num_bytes = bytes_needed(size);
    data = new unsigned char[num_bytes];
    
    //initialize all bytes to either 0x00 or 0xFF based on the default value
    std::memset(data, default_value ? 0xFF : 0x00, num_bytes);
    
    //if default_value is true, we need to clear any excess bits in the last byte
    if (default_value && size % 8 != 0) {
        size_t last_byte = num_bytes - 1;
        // create a mask for valid bits:~~~> 00011111 for 5 bits
        unsigned char mask = (1 << (size % 8)) - 1;
        data[last_byte] &= mask;
    }
}
//copy cons
BoolArray::BoolArray(const BoolArray& other) : num_bits(other.num_bits) {
    if (num_bits == 0) {
        data = nullptr;
        return;
    }
    
    size_t num_bytes = bytes_needed(num_bits);
    data = new unsigned char[num_bytes];
    std::memcpy(data, other.data, num_bytes);
}

BoolArray::~BoolArray() {
    delete[] data;
}

//assignment op
BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        
        num_bits = other.num_bits;
        
        if (num_bits == 0) {
            data = nullptr;
            return *this;
        }
        
        size_t num_bytes = bytes_needed(num_bits);
        data = new unsigned char[num_bytes];
        std::memcpy(data, other.data, num_bytes);
    }
    return *this;
}

//mon-const element access
BoolArray::BitReference BoolArray::operator[](size_t index) {
    if (index >= num_bits) {
        throw std::out_of_range("BoolArray index out of range");
    }
    return BitReference(*this, index);
}

//const element access
bool BoolArray::operator[](size_t index) const {
    if (index >= num_bits) {
        throw std::out_of_range("BoolArray index out of range");
    }
    
    size_t byte_index = index / 8;
    unsigned char bit_mask = 1 << (index % 8);
    
    return (data[byte_index] & bit_mask) != 0;
}

//debug method
void BoolArray::print_bits() const {
    size_t num_bytes = bytes_needed(num_bits);
    for (size_t i = 0; i < num_bytes; ++i) {
        for (int bit = 7; bit >= 0; --bit) {
            std::cout << ((data[i] & (1 << bit)) ? "1" : "0");
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

//resize ~~~~~~~~~~~~~~~~~~~~~> *ToAsk: 
void BoolArray::resize(size_t new_size, bool fill_value) {
    if (new_size == num_bits) {
        return;
    }
    
    //if resizing to 0 ~~~> just delete the data
    if (new_size == 0) {
        delete[] data;
        data = nullptr;
        num_bits = 0;
        return;
    }
    
    size_t old_bytes = bytes_needed(num_bits);
    size_t new_bytes = bytes_needed(new_size);
    unsigned char* new_data = new unsigned char[new_bytes];
    
    if (fill_value) {
        //fill with 1s
        std::memset(new_data, 0xFF, new_bytes);
    } else {
        //fill 0s
        std::memset(new_data, 0x00, new_bytes);
    }
    
    //if we already had data ~~> copy the existing bits
    if (data != nullptr) {
        size_t bytes_to_copy = std::min(old_bytes, new_bytes);
        std::memcpy(new_data, data, bytes_to_copy);
    }
    
    // ~~~~~~~~~~ headache here, self note
    if (new_size > num_bits && fill_value && num_bits % 8 != 0) {
        size_t overlap_byte = num_bits / 8;
        if (overlap_byte < new_bytes) { 
            unsigned char exist_mask = (1 << (num_bits % 8)) - 1;  //~~~> mask
            new_data[overlap_byte] = (data[overlap_byte] & exist_mask) | (~exist_mask & 0xFF); //keep existing >> set new to 1
        }
    }
    
    //when shrinking ~~>clear any excess bits in the last byte (????? overflow??)
    if (new_size % 8 != 0) {
        size_t last_byte = (new_size - 1) / 8;
        unsigned char valid_mask = (1 << (new_size % 8)) - 1;
        
        if (fill_value) {
            //for true fill value: clear invalid bits and keep valid bits
            new_data[last_byte] = new_data[last_byte] & valid_mask;
        } else {
            //for false fill value: clear all bits (~~>already done)
        }
    }
    
    //replace old data with new data
    delete[] data;
    data = new_data;
    num_bits = new_size;
}