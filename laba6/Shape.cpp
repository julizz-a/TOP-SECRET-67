#include "Shape.h"

QString Shape::getInfo() const
{
    return QString("%1: Площадь = %2, Периметр = %3")
        .arg(name())
        .arg(area())
        .arg(perimeter());
}
