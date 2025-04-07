#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
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
        delete[] data [i];
    }
    delete[] data;
    cout<<"matrix des called"<<endl;
}
//assignment operator
Matrix& Matrix::operator=(const Matrix &other){
    if (this != &other) {
        for(int i=0; i<rows;i++){
            delete[] data[i];
        }
        delete[] data;
        rows=other.rows;
        columns=other.columns;
        data = new double*[rows];
        for (int i=0; i<rows; i++){
            data[i] = new double[columns];
        }
        for(int i=0;i<rows;i++){
            for(int j =0;j<columns; j++){
                data[i][j]=other.data[i][j];
            }
        }

    }
    return *this;
}

//ops

//+=
Matrix& Matrix::operator+=(const Matrix& other){
    if ( rows !=other.rows || columns != other.columns ){
        throw std::invalid_argument("matrixs have different dimentions");
    }
    add_in_place(const_cast<Matrix&>(other));
    return *this;
}
//-=
Matrix& Matrix::operator-=(const Matrix& other){
    if ( rows !=other.rows || columns != other.columns ){
        throw std::invalid_argument("matrixs have different dimentions");
    }
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
}
//*=
Matrix& Matrix::operator*=(double scalar){
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            data[i][j] *= scalar;
        }
    }
    return *this;
}
///=
Matrix& Matrix::operator/=(double scalar){
    if (scalar ==0 ){
        throw std::invalid_argument("can't divide by 0");
    }
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            data[i][j] /= scalar;
        }
    }
    return *this;
}
// +
Matrix Matrix::operator+(const Matrix& other) const{
    if ( rows !=other.rows || columns != other.columns ){
        throw std::invalid_argument("matrixs have different dimentions");
    }
    Matrix result(*this);
    result.add_in_place(const_cast<Matrix&>(other));
    return result;

}
// -
Matrix Matrix::operator-(const Matrix& other) const{
    if ( rows !=other.rows || columns != other.columns ){
        throw std::invalid_argument("matrixs have different dimentions");
    }
    Matrix result(*this);
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            result.data[i][j] -= other.data[i][j];
        }
    
    }
    return result;
}
// *
Matrix Matrix::operator*(const Matrix& other) const{
    if (rows != other.columns ) {
        throw std::invalid_argument ("can't multiply, rows/cols dont match");
    }
    Matrix result(*this);

    result.multiply(const_cast<Matrix&>(other));
    return result;
}
Matrix Matrix::operator*(double scalar){
    
    Matrix result(*this);
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            result.data[i][j] *= scalar;
        }
    }
    return result;
}
// / 
Matrix Matrix::operator/(double scalar){
    if (scalar == 0 ){
        throw std::invalid_argument("cant divite by 0");
    }
    Matrix result(*this);
    for (int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            result.data[i][j] /= scalar;
        }
    
    }
    return result;
}
// double * matrix
Matrix operator*(double scalar, const Matrix& m){
    Matrix result(m);
    for (int i=0; i<result.rows; i++){
        for(int j=0; j<result.columns; j++){
            result.data[i][j] *= scalar;
        }
    }
    return result;
}
Matrix operator-(const Matrix& m){
    Matrix result(m);
    result.negate();
    return result;
}
//get value

double Matrix::get(int i, int j) const{
     if (i < 0 || i >= rows || j < 0 || j >= columns) {
        throw out_of_range("Index out of bounds");
    }
    return data[i][j];
}

// set 
void Matrix::set(int i, int j, double value) {

     if (i < 0 || i >= rows || j < 0 || j >= columns) {
        throw out_of_range("Index out of bounds");
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
        throw invalid_argument("Matrix dimensions must match for addition");
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
        throw invalid_argument("Incompatible matrix dimensions for multiplication");
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


//[print]
void Matrix::print(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <columns; j++) {
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

}