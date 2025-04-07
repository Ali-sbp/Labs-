#ifndef SHORTARRAY_HPP
#define SHORTARRAY_HPP

#include <cstddef> 

class ShortArray {
    private :
    short* data;
    size_t capacity;
    size_t count;
    void allocate(size_t new_capacity);
    void deallocate();

    public:
    ShortArray();
    explicit ShortArray(size_t size); 
    ShortArray(size_t size,short value); //size/val cons
    ShortArray(const ShortArray& other); //copy cons
    ~ShortArray();

    //operators
    ShortArray& operator=(const ShortArray& other); //assignment
    short& operator[](size_t index);
    const short& operator[](size_t index) const; //const version of index ops

    //methods
    void push(short new_val); //add element
    short pop(); //removes
    size_t size() const; //get current size
    void resize(size_t newSize, short fillValue =0); //change array size

};

#endif //ShortArray