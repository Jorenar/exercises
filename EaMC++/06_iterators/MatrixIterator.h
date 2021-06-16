#pragma once

#include <initializer_list>

#include <numeric> // for std::accumulate and std::inner_product

class MatrixException : public std::runtime_error {
  public:
    MatrixException(const char*  msg) : runtime_error(msg) {}
    MatrixException(std::string& msg) : runtime_error(msg) {}
};

template<typename T = double, size_t N = 0, size_t M = 0>
class Matrix {
  public:

    Matrix()
    {
        for (T& x: data) {
            x = 0;
        }
    }

    Matrix(bool) {}  // constructor without initialization

    Matrix(int, int, bool) {} // constructor without initialization

    Matrix(std::initializer_list<std::initializer_list<T>> l)
    {
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
    }

    constexpr size_t numberOfColumns() const { return M; }
    constexpr size_t numberOfRows() const { return N; }
    T  operator ()(size_t n, size_t m) const { return data[getIndex(n, m)]; }
    T& operator ()(size_t n, size_t m) { return data[getIndex(n, m)]; }
    T* getData() { return data; }
    const T* getData() const { return data; }


    // ITERATORS -----------------------

    class iterator;

    inline iterator begin() { return iterator(&((*this)(1,1)), 1); }
    inline iterator end() { return iterator(&((*this)(N,M+1)), 1); }


    using row_iterator = iterator;

    inline row_iterator row_begin(size_t n)
    {
        return row_iterator(&((*this)(n,1)), 1);
    }

    inline row_iterator row_end(size_t n)
    {
        return row_iterator(&((*this)(n,M+1)), 1);
    }


    using col_iterator = iterator;

    inline col_iterator col_begin(size_t m)
    {
        return col_iterator(&((*this)(1,m)), M);
    }

    inline col_iterator col_end(size_t m)
    {
        return col_iterator(&((*this)(N+1,m)), M);
    }

  private:

    const size_t getIndex(const size_t n, const size_t m) const
    {
        size_t idx = (n-1)*M + m-1;
        //if (idx >= N*M || n > N || m > M) {
        //    std::string msg = "Requested wrong indexes [" + std::to_string(n)
        //        + "," + std::to_string(m) + "]";
        //    throw MatrixException(msg);
        //}
        return idx;
    }

    T data[N*M];
};

template<typename T, size_t N, size_t M>
class Matrix<T,N,M>::iterator {
  public:
    iterator(T* c, size_t o) : current(c), offset(o) {}

    bool operator !=(const iterator& obj) { return current != obj.current; }
    bool operator ==(const iterator& obj) { return current == obj.current; }

    iterator& operator ++() { current += offset; return *this; }
    iterator& operator --() { current -= offset; return *this; }

    iterator operator ++(int)
    {
        iterator temp(*this);
        current += offset;
        return temp;
    }

    iterator operator --(int)
    {
        iterator temp(*this);
        current -= offset;
        return temp;
    }

    T& operator *() { return *current; }
    T  operator *() const { return *current; }

    T* operator ->() const { return current; }

  private:
    T* current;
    size_t offset;
};

// vim: ft=cpp fen
