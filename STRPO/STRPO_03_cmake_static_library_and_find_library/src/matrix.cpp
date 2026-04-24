#include "ds/matrix.hpp"

#include <stdexcept>

namespace ds {

Matrix::Matrix(int n) : rows_(n), cols_(n), data_{} {
    if (n <= 0 || n > kMaxSize) throw std::invalid_argument("matrix size out of range");
    for (int i = 0; i < n; ++i) data_[i][i] = 1.0;
}

Matrix::Matrix(int m, int n, double fill_value) : rows_(m), cols_(n), data_{} {
    if (m <= 0 || n <= 0 || m > kMaxSize || n > kMaxSize) throw std::invalid_argument("matrix size out of range");
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] = fill_value;
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_{} {
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] = other.data_[i][j];
}

Matrix::Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_{} {
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) {
        data_[i][j] = other.data_[i][j];
        other.data_[i][j] = 0.0;
    }
    other.rows_ = 1; other.cols_ = 1; other.data_[0][0] = 1.0;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows_ = other.rows_; cols_ = other.cols_;
        for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] = other.data_[i][j];
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        rows_ = other.rows_; cols_ = other.cols_;
        for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
            other.data_[i][j] = 0.0;
        }
        other.rows_ = 1; other.cols_ = 1; other.data_[0][0] = 1.0;
    }
    return *this;
}

void Matrix::validate_indices(int i, int j) const { if (i < 0 || j < 0 || i >= rows_ || j >= cols_) throw std::out_of_range("matrix index out of range"); }
double Matrix::get(int i, int j) const { validate_indices(i, j); return data_[i][j]; }
void Matrix::set(int i, int j, double value) { validate_indices(i, j); data_[i][j] = value; }
int Matrix::get_height() const { return rows_; }
int Matrix::get_width() const { return cols_; }
void Matrix::negate() { for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] = -data_[i][j]; }
void Matrix::add_in_place(const Matrix& other) { *this += other; }
Matrix Matrix::multiply(const Matrix& other) const { return *this * other; }

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) throw std::invalid_argument("matrix sizes do not match");
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] += other.data_[i][j];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) throw std::invalid_argument("matrix sizes do not match");
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] -= other.data_[i][j];
    return *this;
}

Matrix& Matrix::operator*=(double value) { for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] *= value; return *this; }
Matrix& Matrix::operator/=(double value) {
    if (value == 0.0) throw std::invalid_argument("division by zero");
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) data_[i][j] /= value;
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const { Matrix result(*this); result += other; return result; }
Matrix Matrix::operator-(const Matrix& other) const { Matrix result(*this); result -= other; return result; }
Matrix Matrix::operator*(double value) const { Matrix result(*this); result *= value; return result; }
Matrix Matrix::operator/(double value) const { Matrix result(*this); result /= value; return result; }

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) throw std::invalid_argument("matrix sizes are not compatible");
    Matrix result(rows_, other.cols_, 0.0);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            double value = 0.0;
            for (int k = 0; k < cols_; ++k) value += data_[i][k] * other.data_[k][j];
            result.data_[i][j] = value;
        }
    }
    return result;
}

Matrix operator*(double value, const Matrix& matrix) { return matrix * value; }
Matrix operator-(const Matrix& matrix) { Matrix result(matrix); result.negate(); return result; }

long long fibonacci_matrix(int n) {
    if (n < 0) throw std::invalid_argument("n must be non-negative");
    if (n == 0) return 0;
    if (n == 1) return 1;
    Matrix transform(2, 2, 0.0);
    transform.set(0,0,1.0); transform.set(0,1,1.0); transform.set(1,0,1.0); transform.set(1,1,0.0);
    Matrix result(2);
    int power = n - 1;
    while (power > 0) {
        if (power & 1) result = result * transform;
        transform = transform * transform;
        power >>= 1;
    }
    return static_cast<long long>(result.get(0,0));
}

}  // namespace ds
