#include "Point.hpp"
#include <cmath>
#include <iostream>

Point::Point() : x(0) , y(0) {}

Point::Point(double a, double b) : x(a) , y(b) {}

Point::~Point() {}

//copy const
Point::Point(const Point& other) : x(other.x) , y(other.y) {}

//assignment op
Point& Point::operator=(const Point& other){
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

double Point::getX() const {
    return x;
}
double Point::getY() const{
    return y;
}
void Point::setX(double newX) {
    x = newX;
}
void Point::setY(double newY) {
    y = newY;
}

double Point::Distance(const Point& other) const {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}
double Point::OriginDistance() const{
    return sqrt(pow(x , 2)+ pow(y , 2));
}

//ops
bool Point::operator==(const Point& other)const{
    return ( x == other.x && y == other.y);
}
bool Point::operator!=(const Point& other)const{
    return !(*this == other);
}

void Point::print(std::ostream& os)const{
    os << "x= " << x << " , y = " << y << std::endl;
}
