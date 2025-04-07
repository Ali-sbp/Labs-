#include "Point.hpp"

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle {

    private:
    Point Center;
    double Radius;

    public:
    //constructors
    Circle();
    Circle(Point CenterP, double R);
    Circle(double a, double b, double R);

    //copy const
    Circle(const Circle& other);
    
    //destructor
    ~Circle();

    //assignment operator
    Circle& operator=(const Circle& other);

    //methods
    void setRadius(double R);
    void setCenter(Point C);
    double getRadius()const;
    Point getCenter()const ;

    double getArea() const;
    double circumference()const;

    //comparison operators
    bool operator==(const Circle& other)const;
    bool operator!=(const Circle& other)const;
    //print with flexible os stream
    void print(std::ostream& os = std::cout)const;
};

#endif // CIRCLE_HPP