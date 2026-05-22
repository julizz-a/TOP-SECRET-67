#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h);

    double area() const override;
    double perimeter() const override;
    QString name() const override;

    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

#endif
