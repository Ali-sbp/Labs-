#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

//identity
Matrix::Matrix (int n) : rows (n), columns(n) {
    data = new double* [rows];
    for (int i=0; i<rows; i++){
        data[i] = new double [columns];
        data [i][i]= 1.0;

    }
}
//fill value

Matrix::Matrix(int m , int n, double fill_value): rows(m), columns(n) {
    data = new double*[rows];
    for (int i=0; i<rows; i++){
        data [i]= new double [columns];
        for(int j=0; j<columns; j++){
        data[i][j]= fill_value;
        }
    }

}
//copy
Matrix::Matrix(const Matrix &other) : rows(other.rows), columns(other.columns) {
    data = new double* [rows];
    for (int i=0; i<rows; i++){
        data [i]= new double [columns];
        for(int j=0; j<columns; j++){
            data [i][j]= other.data [i][j];
        }
    }
}
//destructor
Matrix::~Matrix(){
    for(int i=0; i<rows; i++){
        delete data [i];
    }
    delete data;
}

//get value

double Matrix::get(int i, int j) const{
     if (i < 0 || i >= rows || j < 0 || j >= columns) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i][j];
}

// set 
void Matrix::set(int i, int j, double value) {

     if (i < 0 || i >= rows || j < 0 || j >= columns) {
        throw std::out_of_range("Index out of bounds");
    }
    data[i][j]= value; 
}
// get height
int Matrix::get_height() const{
    return rows;
}
//get width
int Matrix::get_width() const {
    return columns;
}
// -A
void Matrix::negate(){
       for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            data[i][j] = -data[i][j];
        }
    }
}
//add in place 
void Matrix::add_in_place(Matrix &other){
    if (rows != other.rows || columns != other.columns) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    for(int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            data[i][j] += other.data[i][j];
        }
    }
}
//multiply
Matrix Matrix::multiply(Matrix &other) const{
    if (columns != other.rows) {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
    }
    Matrix result(rows, other.columns, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.columns; j++) {
            for (int k = 0; k < columns; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}