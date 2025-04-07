#include "Circle.hpp"
#include "Point.hpp"
#include <cmath>
#include <iostream>

Circle::Circle() : Center(0,0) , Radius(0) {}
Circle::Circle(Point CenterP,double R) : Center(CenterP.getX() , CenterP.getY()), Radius(R) {} 
Circle::Circle(double a, double b, double R) : Center(a,b) , Radius (R) {}

//copy const
Circle::Circle(const Circle& other) : Center(other.Center), Radius(other.Radius) {} 

// destructor
Circle::~Circle() {}
//aassignment op
Circle& Circle::operator=(const Circle& other){
    if (this != &other) {
        Center = other.Center;
        Radius = other.Radius;
    }
    return *this;
}
//methods
void Circle::setRadius(double R){
    Radius = R;
}
void Circle::setCenter(Point C){
    Center = C;
}
Point Circle::getCenter()const{
    return Center;
}
double Circle::getRadius()const{
    return Radius;
}
double Circle::getArea()const{
    return M_PI * pow(Radius,2);
}
double Circle::circumference()const{
    return M_PI * 2 * Radius;
}
//comparison operators
bool Circle::operator==(const Circle& other)const{
    return (Center == other.Center && Radius == other.Radius);
}
bool Circle::operator!=(const Circle& other)const{
    return !(*this == other);
}
void Circle::print(std::ostream& os)const{
os << "center = (x=" << Center.getX() << ", y=" << Center.getY() << "), radius = " << Radius << std::endl;
}