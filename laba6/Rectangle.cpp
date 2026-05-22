#include "Rectangle.hpp"

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

double Rectangle::area() const
{
    return width * height;
}

double Rectangle::perimeter() const
{
    return 2 * (width + height);
}

QString Rectangle::name() const
{
    return "Прямоугольник";
}
