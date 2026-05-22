# pragma once

namespace mt {
    class Matrix {
    private:
        // поле
        int rows_;
        int cols_;
        int** data_; // int* указывает на data[i], int** указывает на data[i][j]

    public:
        // конструкторы
        Matrix();
        Matrix(size_t n, size_t m);
        Matrix(const Matrix& other);
        ~Matrix();

        // метод
        int& Data(int i, int j) const;
        void Set(int i, int j, int k);
        void Print() const ;
        void Print2(const Matrix& k);

        // оператор присваивания копированием
        Matrix& operator=(const Matrix& other);

        // геттер
        int get_rows() const;
        int get_cols() const;
    };
}


//сложнааа (помогите)