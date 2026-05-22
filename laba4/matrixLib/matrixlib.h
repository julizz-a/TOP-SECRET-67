# pragma once

namespace mt {
class Matrix {
private:
    // поле
    int rows_;
    int cols_;
    double** data_;

public:
    // конструкторы
    Matrix();
    Matrix(int n, int m);
    Matrix(const Matrix& other);
    ~Matrix();

    // ПЕРЕГРУЗКА ОПЕРАТОРОВ
    Matrix operator+(const Matrix& other) const;  // оператор сложения
    Matrix& operator++();      // префиксный инкремент (++x)
    Matrix operator++(int);    // постфиксный инкремент (x++)

    // метод
    double& Data(int i, int j)const;
    void Set(int i, int j, double k);
    void Print() const ;
    void Print2(const Matrix& k);

    // оператор присваивания копированием
    Matrix& operator=(const Matrix& other);

    // геттер
    int get_rows() const;
    int get_cols() const;
    bool isEmpty() const { return rows_ == 0 || cols_ == 0 || data_ == nullptr; }
};
}


//сложнааа (помогите)
