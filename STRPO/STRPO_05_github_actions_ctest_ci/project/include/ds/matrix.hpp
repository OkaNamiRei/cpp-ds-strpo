#pragma once

namespace ds {

class Matrix {
public:
    static constexpr int kMaxSize = 16;

    Matrix(int n = 1);
    Matrix(int m, int n, double fill_value);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix() = default;

    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const;
    int get_width() const;

    void negate();
    void add_in_place(const Matrix& other);
    Matrix multiply(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double value);
    Matrix& operator/=(double value);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double value) const;
    Matrix operator/(double value) const;

private:
    int rows_;
    int cols_;
    double data_[kMaxSize][kMaxSize];

    void validate_indices(int i, int j) const;
};

Matrix operator*(double value, const Matrix& matrix);
Matrix operator-(const Matrix& matrix);
long long fibonacci_matrix(int n);

}  // namespace ds
