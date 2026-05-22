#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.h"

class Triangle : public Shape
{
private:
    double sideA;
    double sideB;
    double sideC;

public:
    Triangle(double a, double b, double c);

    double area() const override;
    double perimeter() const override;
    QString name() const override;

    bool isValid() const;

    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
};

#endif // TRIANGLE_HPP
