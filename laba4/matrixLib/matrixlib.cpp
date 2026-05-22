#include "matrixlib.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <QDebug>

namespace mt {

Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(int n, int m) : rows_(n), cols_(m) {
    if (n < 0 || m < 0) {
        throw std::invalid_argument("Размеры не могут быть отрицательными");
    }
    if (n == 0 || m == 0) {
        rows_ = 0;
        cols_ = 0;
        data_ = nullptr;
        return;
    }

    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_]();
    }
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {

    if (other.isEmpty()) {
        data_ = nullptr;
        return;
    }

    data_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new double[cols_];
        std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
    }
}

Matrix::~Matrix() {
    if (data_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
}

// ПЕРЕГРУЗКА ОПЕРАТОРА СЛОЖЕНИЯ
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Матрицы должны быть одинакового размера для сложения!");
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
        }
    }
    return result;
}

// ПРЕФИКСНЫЙ ИНКРЕМЕНТ (++matrix)
Matrix& Matrix::operator++() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ++data_[i][j];
        }
    }
    return *this;
}

// ПОСТФИКСНЫЙ ИНКРЕМЕНТ (matrix++)
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}


double& Matrix::Data(int i, int j)const{
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data_[i][j];
}

void Matrix::Set(int i, int j, double k) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    data_[i][j] = k;
}

void Matrix::Print() const {
    if (isEmpty()) {
        std::cout << "Пустая матрица" << std::endl;
        return;
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            qInfo() << data_[i][j] << " ";
        }
        qInfo() << "\n";
    }
}

void Matrix::Print2(const Matrix& k) {
    k.Print();
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    if (data_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    if (!other.isEmpty()) {
        data_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_];
            std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
        }
    }
    return *this;
}

int Matrix::get_rows() const { return rows_; }
int Matrix::get_cols() const { return cols_; }

}

