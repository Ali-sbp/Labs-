#include <cmath>
#include <iostream>


#ifndef POINT_HPP
#define POINT_HPP


class Point {
    private:
    double x; 
    double y;
    
    public:

    Point();
    
    Point(double a,double b);

    ~Point();

    //copy const
    Point(const Point& other);

    //assignment operator
    Point& operator=(const Point& other);

    //methods
    double getX() const;
    double getY() const;
    void setX(double newX);
    void setY(double newY);
    
    double Distance(const Point& other)const;
    double OriginDistance() const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    void print(std::ostream& os = std::cout)const;

};


#endif //POINT_HPP