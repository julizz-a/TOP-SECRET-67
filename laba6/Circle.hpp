#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.h"

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r);

    double area() const override;
    double perimeter() const override;
    QString name() const override;

    double getRadius() const { return radius; }
};

#endif // CIRCLE_HPP
