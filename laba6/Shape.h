#ifndef SHAPE_H
#define SHAPE_H

#include <QString>

//Наследие - это механизм ООП, позволяющий создавать новый класс на основе существующего класса. Новый класс наследует свойства и методы существующего класса
//Полиморфизм - способность объектов с одинаковым интерфейсом иметь различную реализацию.

/*private:
    int a;  // НЕ наследуется (приватные члены)
protected:
    int b;  // Наследуется как protected/public в зависимости от типа наследования
public:
    int c;  // Наследуется как public/protected/private в зависимости от типа наследования
    void func();  // Наследуется
*/

class Shape
{
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QString name() const = 0;

    virtual QString getInfo() const;
};

#endif
