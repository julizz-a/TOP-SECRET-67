#include "matrix.hpp"
#include <iostream>

namespace mt {
// Конструкторы
Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(size_t n, size_t m) : rows_(n), cols_(m), data_(nullptr) {
    data_ = new int* [rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_]();
    }
}

Matrix::Matrix(const Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = new int* [rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
    }
}

//Деструктор
Matrix::~Matrix() {
    if (data_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
    }
}

// Методы
void Matrix::Set(int i, int j, int k) {
    if (i >= 0 && i < rows_ && j >= 0 && j < cols_) {
        data_[i][j] = k;
    }
}

int Matrix::Get(int i, int j) const {
    if (i >= 0 && i < rows_ && j >= 0 && j < cols_) {
        return data_[i][j];
    }
    return 0;
}

void Matrix::Print() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << data_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// оператор присваивания копированием
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = new int* [rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
    }
    return *this;
}

// Оператор сложения
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices dimensions must match for addition");
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
        }
    }
    return result;
}

// Префиксный инкремент
Matrix& Matrix::operator++() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ++data_[i][j];
        }
    }
    return *this;
}

// Постфиксный инкремент
Matrix Matrix::operator++(int) {
    Matrix temp = *this;
    ++(*this);
    return temp;
}

// геттеры
int Matrix::get_rows() const { return rows_; }
int Matrix::get_cols() const { return cols_; }
}
