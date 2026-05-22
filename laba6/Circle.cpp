#include "Circle.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle::Circle(double r)
    : radius(r)
{
}

double Circle::area() const
{
    return M_PI * radius * radius;
}

double Circle::perimeter() const
{
    return 2 * M_PI * radius;
}

QString Circle::name() const
{
    return "Круг";
}
