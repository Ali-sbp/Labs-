#include "ShortArray.hpp"
#include <stdexcept>
#include <algorithm> //std::copy
//allocate
void ShortArray::allocate(size_t newCapacity){
    short* newData= new short[newCapacity];
    if(data){
        for (size_t i=0;i<count;i++){
            newData[i]=data[i];
        }
        delete [] data;
    }
    data = newData;
    capacity=newCapacity;
}
void ShortArray::deallocate() {
    if(data){
        delete [] data;
        data = nullptr;
    }
    capacity = 0;
    count = 0;
}
ShortArray::ShortArray() : data(nullptr) , capacity (0), count (0) {}

ShortArray::ShortArray(size_t size) : data(nullptr), capacity(0), count(0){
    resize(size);
}

ShortArray::ShortArray(size_t size,short value): data(nullptr), capacity(0), count (0){
    resize(size,value);
}

ShortArray::ShortArray(const ShortArray& other) : data(nullptr), capacity(0), count(0){
    if (other.count > 0){
        allocate(other.count);
        count = other.count;
        for (size_t i=0; i<count ; i++){
            data[i]= other.data[i];
        }
    }
}
ShortArray::~ShortArray(){
    deallocate();
}

//ops
ShortArray& ShortArray::operator=(const ShortArray& other){
    if (this != &other) {
        deallocate();
        if (other.count > 0){
            allocate(other.count);
            count = other.count;
            for (size_t i=0;i<count; i++){
                data[i] = other.data[i];
            }
        }
    }
    return *this;
}
short& ShortArray::operator[](size_t index){
    if (index >= count){
        throw std::out_of_range("index out of range");
    }
    return data[index];
}
const short& ShortArray::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("index out of range");
    }
    return data[index];
}
//add elemnt 

void ShortArray::push(short newVal){
    if(count == capacity){ 
        size_t newCapacity= capacity == 0 ? 1 : capacity *2;
        allocate(newCapacity);
    }
    data[count++]=newVal;
}
short ShortArray::pop(){
    if (count ==0) {
        throw std::runtime_error("cant pop from empty array");
    }
    return data[--count];
}
size_t ShortArray::size() const {
    return count;
}

void ShortArray::resize(size_t newSize, short fillValue){
    if(newSize==count){
        return;
    }
    if (newSize== 0){
        deallocate();
        return;
    }
    if(newSize<count){
        count=newSize;
        return;
    }
    if (newSize > capacity){
       allocate(newSize);
    }
    for(size_t i=count; i< newSize ; i++){
        data[i]=fillValue;
    }
    count=newSize;
}

