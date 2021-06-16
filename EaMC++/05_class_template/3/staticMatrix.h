#pragma once

#include <initializer_list>
#include <iostream>

class MatrixException : public std::runtime_error {
  public:
    MatrixException(const char*  msg) : runtime_error(msg) {}
    MatrixException(std::string& msg) : runtime_error(msg) {}
};

std::ostream& stddbg = std::cout;

template<typename T = double, size_t N = 0, size_t M = 0>
class Matrix {
  public:

    Matrix()
    {
        stddbg << " constructor of static " << N << "x" << M << " matrix" << std::endl;
        for (T& x: data) {
            x = 0;
        }
    }

    Matrix(int)  // constructor without initialization
    {
        stddbg << " constructor of static uninitialized matrix" << std::endl;
    }

    Matrix(std::initializer_list<std::initializer_list<T>> l)
    {
        stddbg << " constructor of static " << N << "x" << M
            << " matrix from initializer_list" << std::endl;
        size_t i = 0;
        for (auto x: l) {
            for (auto y: x) {
                data[i++] = y;
                if (i % M == x.size()) {
                    i += M - x.size();
                }
            }
        }
    }

    Matrix(const Matrix& obj)  // copy constructor
    {
        stddbg << " copy constructor of static matrix" << std::endl;
        std::copy(obj.data, obj.data+(N*M), data);
    }

    Matrix operator +(const Matrix& obj) const
    {
        Matrix<T, N, M> temp(1);
        for (size_t i = 0; i < N*M; i++) {
            temp.data[i] = data[i] + obj.data[i];
        }
        return temp;
    }

    Matrix operator +(const Matrix<T,0,0>& obj) const
    {
        if (N != obj.numberOfRows() || M != obj.numberOfColumns()) {
            throw MatrixException("Incompatible dimensions in operator +");
        }
        Matrix<T, N, M> temp(1);
        const T* objData = obj.getData();
        for (size_t i = 0; i < N*M; i++) {
            temp.data[i] = data[i] + objData[i];
        }
        return temp;
    }

    template<size_t X>
    constexpr Matrix<T, N, X> operator *(const Matrix<T, M, X>& obj) const
    {
        Matrix<T, N, X> temp(1);
        for (size_t i = 1; i <= N; i++) {
            for (size_t j = 1; j <= X; j++) {
                temp(i,j) = T{};
                for (size_t k = 1; k <= M; k++) {
                    temp(i, j) += (*this)(i, k) * obj(k, j);
                }
            }
        }
        return temp;
    }

    Matrix<T,0,0> operator *(const Matrix<T,0,0>& obj) const
    {
        size_t X = obj.numberOfColumns();
        if (M != obj.numberOfRows()) {
            throw MatrixException("Incompatible dimensions in operator *");
        }
        Matrix<T,0,0> temp(N, X, 1);
        for (size_t i = 1; i <= N; i++) {
            for (size_t j = 1; j <= X; j++) {
                temp(i,j) = T{};
                for (size_t k = 1; k <= M; k++) {
                    temp(i, j) += (*this)(i, k) * obj(k, j);
                }
            }
        }
        return temp;
    }

    Matrix(Matrix<T,0,0>& obj)
    {
        T* objData = obj.getData();
        std::copy(objData, objData+(N*M), data);
        stddbg << " conversion from dynamic to static matrix" << std::endl;
    }

    constexpr size_t numberOfColumns() const { return M; }
    constexpr size_t numberOfRows() const { return N; }
    T  operator ()(size_t n, size_t m) const { return data[getIndex(n, m)]; }
    T& operator ()(size_t n, size_t m) { return data[getIndex(n, m)]; }
    T* getData() { return data; }
    const T* getData() const { return data; }

  private:

    const size_t getIndex(const size_t n, const size_t m) const
    {
        size_t idx = (n-1)*M + m-1;
        if (idx >= N*M || n > N || m > M) {
            std::string msg = "Requested wrong indexes [" + std::to_string(n)
                + "," + std::to_string(m) + "]";
            throw MatrixException(msg);
        }
        return idx;
    }

    T data[N*M];
};

// vim: ft=cpp fen fdl=1
