#pragma once

#include <initializer_list>
#include <iostream>

template<typename T = double, size_t N = 0, size_t M = 0>
class Matrix {
  public:

    Matrix()
    {
        std::cout << "constructor of static " << N << "x" << M << " matrix" << std::endl;
        for (T& x: data) {
            x = 0;
        }
    }

    Matrix(int)  // constructor without initialization
    {
        std::cout << "constructor of static uninitialized matrix" << std::endl;
    }

    Matrix(std::initializer_list<std::initializer_list<T>> l)
    {
        std::cout << "constructor of static " << N << "x" << M
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
        std::cout << "copy constructor of static matrix" << std::endl;
        std::copy(obj.data, obj.data+(N*M), data);
    }

    const size_t numberOfRows() const
    {
        return N;
    }

    const size_t numberOfColumns() const
    {
        return M;
    }

    T  operator ()(size_t n, size_t m) const
    {
        return data[getIndex(n, m)];
    }

    T& operator ()(size_t n, size_t m)
    {
        return data[getIndex(n, m)];
    }

    constexpr Matrix operator +(const Matrix& obj) const
    {
        Matrix<T, N, M> temp(1);
        for (size_t i = 0; i < N*M; i++) {
            temp.data[i] = data[i] + obj.data[i];
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

  private:
    const size_t getIndex(const size_t n, const size_t m) const
    {
        size_t idx = (n-1)*M + m-1;
        if (idx >= N*M || n > N || m > M) {
            std::cerr << "Wrong indexes!" << std::endl;
            std::cerr << "  Requested: [" << n << ", " << m << "]" << std::endl;
            std::cerr << "  Maximal:   [" << N << ", " << M << "]" << std::endl;
            std::cerr << " Returning last available" << std::endl;
            idx = N == 0 || M == 0 ? 0 : (N-1)*M + M-1;
        }
        return idx;
    }

    T data[N*M];
};

// vim: ft=cpp fen fdl=1
