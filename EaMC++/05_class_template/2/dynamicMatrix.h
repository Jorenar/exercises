#pragma once

#include <memory>
#include <stdexcept>
#include "staticMatrix.h"

std::ostream& stddbg = std::cout;

class MatrixException : public std::runtime_error {
  public:
    MatrixException(const char*  msg) : runtime_error(msg) {}
    MatrixException(std::string& msg) : runtime_error(msg) {}
};

template<typename T>
class Matrix<T,0,0> {
  public:

    Matrix() : N(0), M(0), data(new T[1] {})
    {
        stddbg << " constructor of dynamic " << N << "x" << M << " matrix" << std::endl;
    }

    Matrix(size_t N_, size_t M_) : N(N_), M(M_), data(new T[N*M] {0})
    {
        stddbg << " constructor of dynamic " << N << "x" << M << " matrix" << std::endl;
    }

    Matrix(size_t N_, size_t M_, int) : N(N_), M(M_), data(new T[N*M])
    {
        stddbg << " constructor of uninitialized dynamic " << N << "x" << M << " matrix" << std::endl;
    }

    Matrix(std::initializer_list<std::initializer_list<T>> l) :
        N(l.size()), M(0)
    {
        for (auto x: l) {
            if (x.size() > M) {
                M = x.size();
            }
        }
        data.reset(new T[N*M] {0});
        size_t i = 0;
        for (auto x: l) {
            for (auto y: x) {
                data[i++] = y;
                if (i % M == x.size()) {
                    i += M - x.size();
                }
            }
        }
        stddbg << " constructor of dynamic " << N << "x" << M
            << " matrix from initializer_list" << std::endl;
    }

    Matrix(const Matrix& obj) : // copy constructor
        N(obj.N), M(obj.M)
    {
        data.reset(new T[N*M]);
        std::copy(obj.data.get(), obj.data.get()+(obj.N*obj.M), data.get());
        stddbg << " copy constructor of dynamic matrix" << std::endl;
    }

    Matrix operator +(const Matrix& obj) const
    {
        if (N != obj.numberOfRows() || M != obj.numberOfColumns()) {
            throw MatrixException("Incompatible dimensions in operator +");
        }

        Matrix temp(N, M, 1);
        for (size_t i = 0; i < N*M; i++) {
            temp.data[i] = data[i] + obj.data[i];
        }
        return temp;
    }

    Matrix operator *(const Matrix& obj) const
    {
        size_t X = obj.numberOfColumns();

        if (M != obj.numberOfRows()) {
            throw MatrixException("Incompatible dimensions in operator *");
        }

        Matrix temp(N, X, 1);
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

    T  operator ()(size_t n, size_t m) const { return data[getIndex(n, m)]; }
    T& operator ()(size_t n, size_t m) { return data[getIndex(n, m)]; }
    const size_t numberOfRows() const { return N; }
    const size_t numberOfColumns() const { return M; }

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

    size_t N; // rows
    size_t M; // columns
    std::unique_ptr<T[]> data;
};

// vim: ft=cpp fen fdl=1
