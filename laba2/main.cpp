#include <iostream>
#include "Matrix.hpp"

// Правило трёх
/* если есть нетривиальный деструктор || оператор присваивания копированием || конструктор копирования 
2 варианта:
1. реальзовать все
2. ну или, видимо, не реализовывать ничего (прям запрещаем, типо =delete;, типо прям удаляем их)

нетривиальный - это звёздочка или звёздочки (цитата: возня с динамической памятью)
тревиальный - это просто стандартик, так называемая база, никакой динамической памяти и ничего лишнего получается*/

int main()
{
    // создание разных матриц
    mt::Matrix matrix0;
    std::cout << matrix0.get_rows() << " " << matrix0.get_cols() << std::endl;
    std::cout << std::endl;

	mt::Matrix matrix1(3,4);
    matrix1.Print2(matrix1);
    std::cout << std::endl;

    // заполнение матрицы значениями (от 1 до 12)
    int t = 1;
    for (int i = 0; i < matrix1.get_rows(); ++i) {
        for (int j = 0; j < matrix1.get_cols(); ++j) {
            matrix1.Set(i, j, t);
            ++t;
        }
    }
    matrix1.Print2(matrix1);
    std::cout << std::endl;

    // Конструктор копирования
    mt::Matrix matrix2(matrix1);
    matrix2.Print2(matrix2);
    std::cout << std::endl;

    // оператор присваивания
    mt::Matrix matrix3(2, 2);
    matrix3 = matrix1;
    matrix3.Print2(matrix3);
    std::cout << std::endl;

    // самоприсваивание (работает из-за copy-and-swap)
    matrix1 = matrix1;
    matrix1.Print2(matrix1);
    std::cout << std::endl;

    // цепочка присваиваний
    mt::Matrix matrix4(1, 1);
    mt::Matrix matrix5(4, 6);
    matrix5 = matrix4 = matrix1;
    matrix1.Print2(matrix1);
    std::cout << std::endl;
    matrix4.Print2(matrix4);
    std::cout << std::endl;
    matrix5.Print2(matrix5);
    std::cout << std::endl;
}
