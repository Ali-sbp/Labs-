#include "BoolArrayPC.hpp"
#include <stdexcept>
#include <cstring>


BoolArray::BoolArray() : data(nullptr), num_bits(0) {}

//size constructor with optional default value
BoolArray::BoolArray(size_t size, bool default_value) : num_bits(size) {
    if (size == 0) {
        data = nullptr;
        return;
    }
    
    //allocate memory - each byte holds 8 bits
    size_t num_bytes = bytes_needed(size);
    data = new unsigned char[num_bytes];
    
    //initialize all bytes to either 0x00 or 0xFF based on the default value
    std::memset(data, default_value ? 0xFF : 0x00, num_bytes);
    
    //if default_value is true ~~> clear any excess bits in the last byte
    if (default_value && size % 8 != 0) {
        size_t last_byte = num_bytes - 1;
        unsigned char mask = (1 << (size % 8)) - 1;
        data[last_byte] &= mask;
    }
}

//copy constructor
BoolArray::BoolArray(const BoolArray& other) : num_bits(other.num_bits) {
    if (num_bits == 0) {
        data = nullptr;
        return;
    }
    
    size_t num_bytes = bytes_needed(num_bits);
    data = new unsigned char[num_bytes];
    std::memcpy(data, other.data, num_bytes);
}

//des
BoolArray::~BoolArray() {
    delete[] data;
}

//assignment operator
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

//none-const element access~~> returns a proxy object
BoolProxy BoolArray::operator[](size_t index) {
    if (index >= num_bits) {
        throw std::out_of_range("BoolArray index out of range");
    }
    return BoolProxy(*this, index);
}

//const element access ~~> returns boolean value directly
bool BoolArray::operator[](size_t index) const {
    if (index >= num_bits) {
        throw std::out_of_range("BoolArray index out of range");
    }
    
    size_t byte_index;
    unsigned char bit_mask;
    get_position(index, byte_index, bit_mask);
    
    return (data[byte_index] & bit_mask) != 0;
}

//resize method
void BoolArray::resize(size_t new_size, bool fill_value) {
    if (new_size == num_bits) {
        return;
    }
    
    //if resizing to 0, just delete the data
    if (new_size == 0) {
        delete[] data;
        data = nullptr;
        num_bits = 0;
        return;
    }
    
    size_t old_num_bytes = bytes_needed(num_bits);
    size_t new_num_bytes = bytes_needed(new_size);
    
    //create a new array with the new size
    unsigned char* new_data = new unsigned char[new_num_bytes];
    
    //fill with default value
    std::memset(new_data, fill_value ? 0xFF : 0x00, new_num_bytes);
    
    //copy existing data if any
    if (data != nullptr) {
        std::memcpy(new_data, data, std::min(old_num_bytes, new_num_bytes));
    }
    
    // if we're growing the array and fill_value is true, we need to
    // preserve the existing bits in the overlapping byte
    if (new_size > num_bits && fill_value && num_bits % 8 != 0) {
        size_t overlap_byte = num_bits / 8;
        if (overlap_byte < new_num_bytes) {
            unsigned char mask = (1 << (num_bits % 8)) - 1;
            new_data[overlap_byte] = (new_data[overlap_byte] & ~mask) | (data[overlap_byte] & mask);
        }
    }
    
    //if fill_value is true and we have partial bits in the last byte, clear them
    if (fill_value && new_size % 8 != 0) {
        size_t last_byte = new_num_bytes - 1;
        unsigned char mask = (1 << (new_size % 8)) - 1;
        new_data[last_byte] &= mask;
    }
    
    // swap in the new data
    delete[] data;
    data = new_data;
    num_bits = new_size;
}