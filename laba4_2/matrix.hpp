#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <algorithm>
#include <stdexcept>

namespace mt {
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

public:
    Matrix();
    Matrix(size_t n, size_t m);
    Matrix(const Matrix& other);
    ~Matrix();

    void Set(int i, int j, int k);
    int Get(int i, int j) const;  // геттер
    void Print() const;

    Matrix& operator=(const Matrix& other);

    // Перегруженные операторы
    Matrix operator+(const Matrix& other) const;
    Matrix& operator++();      // префиксный
    Matrix operator++(int);    // постфиксный

    int get_rows() const;
    int get_cols() const;
};
}

#endif // MATRIX_HPP
