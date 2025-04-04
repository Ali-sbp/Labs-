#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
using namespace std;

class Matrix {
    private: 
    int rows;
    int columns; 
    double** data;
    public:
    // identity constructor
    Matrix (int n);
    // mxn fill value const
    Matrix (int m, int n , double fill_value);
    //copy const
    Matrix (const Matrix &other);
    //destructor
    ~Matrix();
    //getters , setters
    double get (int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;
    void negate();
    void add_in_place(Matrix &other);
    Matrix multiply(Matrix &other) const;
    Matrix& operator=(const Matrix &other);
    void print();
};

#endif //MATRIX