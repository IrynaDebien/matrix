#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <windows.h>
using namespace std;

template <typename T>
class Matrix {
private:
    T** data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
    void fillFromKeyboard();
    void fillWithRandom();
    void print() const;
    void setSize(int rows, int cols);
    int getRows() const;
    int getCols() const;
    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator/(const Matrix<T>& other) const;
    T findMax() const;
    T findMin() const;
};



template <typename T>
Matrix<T>::Matrix() : rows(0), cols(0), data(nullptr) {}

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = new T * [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new T[cols];
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    if (data != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new T * [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this == &other) return *this;

    if (data != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    rows = other.rows;
    cols = other.cols;
    data = new T * [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : data(nullptr), rows(0), cols(0) {
    *this = std::move(other);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this == &other) return *this;
    if (data != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    data = other.data;
    rows = other.rows;
    cols = other.cols;
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

template <typename T>
void Matrix<T>::fillFromKeyboard() {
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> data[i][j];
        }
    }
}

template <typename T>
void Matrix<T>::fillWithRandom() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = rand() % 100;
        }
    }
}

template <typename T>
void Matrix<T>::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}

template <typename T>
void Matrix<T>::setSize(int rows, int cols) {
    if (data != nullptr) {
        for (int i = 0; i < this->rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    this->rows = rows;
    this->cols = cols;

    data = new T * [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new T[cols];
    }
}

template <typename T>
int Matrix<T>::getRows() const {
    return rows;
}

template <typename T>
int Matrix<T>::getCols() const {
    return cols;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrices must be of the same size for addition");
    }
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrices must be of the same size for subtraction");
    }
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols != other.rows) {
        throw invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix for multiplication");
    }
    Matrix<T> result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrices must be of the same size for division");
    }

    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (other.data[i][j] == 0) {
                throw invalid_argument("Division by zero is not possible");
            }
            result.data[i][j] = data[i][j] / other.data[i][j];
        }
    }
    return result;
}

template <typename T>
T Matrix<T>::findMax() const {
    T max = data[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] > max) {
                max = data[i][j];
            }
        }
    }
    return max;
}

template <typename T>
T Matrix<T>::findMin() const {
    T min = data[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] < min) {
                min = data[i][j];
            }
        }
    }
    return min;
}