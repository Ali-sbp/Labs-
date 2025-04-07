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
    //friends
    friend Matrix operator*(double scalar, const Matrix& m);
    friend Matrix operator-(const Matrix& m);
    // identity constructor
    Matrix (int n);
    // mxn fill value const
    Matrix (int m, int n , double fill_value);
    //copy const
    Matrix (const Matrix &other);
    //destructor
    ~Matrix();
    //operators
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar);
    Matrix operator/(double scalar);
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
Matrix operator*(double scalar, const Matrix& m);
Matrix operator-(const Matrix& m);

#endif //MATRIX