#include "Triangle.hpp"
#include <cmath>

Triangle::Triangle(double a, double b, double c)
    : sideA(a), sideB(b), sideC(c)
{
}

double Triangle::area() const
{
    double p = perimeter() / 2;
    return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
}

double Triangle::perimeter() const
{
    return sideA + sideB + sideC;
}

QString Triangle::name() const
{
    return "Треугольник";
}

bool Triangle::isValid() const
{
    return (sideA + sideB > sideC) &&
           (sideA + sideC > sideB) &&
           (sideB + sideC > sideA);
}
