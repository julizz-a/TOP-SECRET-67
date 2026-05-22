#include "Matrix.hpp"
#include <cmath>
#include <iostream>

namespace mt {
    // конструкторы
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
        // копирование циклом (бро, долго, сложно и т.д.)
        /*data_ = new int* [rows_];
        for (size_t i = 0; i < rows_; ++i) {
            data_[i] = new int[cols_];
            for (size_t j = 0; j < cols_; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }*/ 
        data_ = new int* [rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new int[cols_];
            std::copy(other.data_[i], other.data_[i] + cols_, data_[i]);
        }
    } 
    Matrix::~Matrix() {
        //if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                delete[] data_[i];
            }
            delete[] data_;
        //}
    }

    // Методы
    int& Matrix::Data(int i, int j) const {
        if (i >= rows_ || j >= cols_) {
            std::cerr << "error" << std::endl;
        }
        return data_[i][j];
    } 

    void Matrix::Set(int i, int j, int k) {
        data_[i][j] = k;
    }

    void Matrix::Print() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << data_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void Matrix::Print2(const Matrix& k) {
        k.Print();
    }

    // оператор присваивания копированием 
    Matrix& Matrix::operator=(const Matrix& other) { // можно убрать константную ссылку и закоментить 1 тмп
        if (this == &other) {
            return *this;
        }
        /* for (int i = 0; i < rows_; ++i) {
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
        return *this; */
        Matrix tmp = other;
        std::swap(tmp.rows_, rows_);
        std::swap(tmp.cols_, cols_);
        std::swap(tmp.data_, data_);
        return *this;
    }

    // геттеры
    int Matrix::get_rows() const { return rows_; }
    int Matrix::get_cols() const { return cols_; }
    }


// аааа что происходит..