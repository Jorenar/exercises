#include <algorithm>
#include <iostream>
#include "matrix.hpp"

// I was unsure whether debug information should be directed to stdout or stderr
//     except for ~Matrix() - there it goes to stderr (for filtering)
std::ostream& stddbg = std::cout;

Matrix::Matrix() : N(0), M(0), data(new double[1]{0}) {}

Matrix::Matrix(size_t N_, size_t M_) : N(N_), M(M_), data(new double[N*M] {0})
{
    stddbg << " constructor of " << N << "x" << M << " matrix" << std::endl;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> l) :
    N(l.size()), M(0)
{
    for (auto x: l) {
        if (x.size() > M) {
            M = x.size();
        }
    }
    data.reset(new double[N*M] {0});
    size_t i = 0;
    for (auto x: l) {
        for (auto y: x) {
            data[i++] = y;
            if (i % M == x.size()) {
                i += M - x.size();
            }
        }
    }
    stddbg << " constructor of " << N << "x" << M
        << " matrix from initializer_list" << std::endl;
}

Matrix::Matrix(const Matrix& obj) : // copy constructor
    N(obj.N), M(obj.M)
{
    data.reset(new double[N*M]);
    std::copy(obj.data.get(), obj.data.get()+(obj.N*obj.M), data.get());
    stddbg << " copy constructor" << std::endl;
}

Matrix::Matrix(Matrix&& obj) : // move constructor
    N(0), M(0), data(nullptr)
{
    std::swap(N, obj.N);
    std::swap(M, obj.M);
    std::swap(data, obj.data);
    stddbg << " move constructor" << std::endl;
}

double Matrix::operator ()(size_t n, size_t m) const
{
    return data[getIndex(n, m)];
}

double& Matrix::operator ()(size_t n, size_t m)
{
    return data[getIndex(n, m)];
}

Matrix& Matrix::operator =(const Matrix& obj) // copy assignment operator
{
    if (this != &obj) {
        N = obj.N;
        M = obj.M;
        data.reset(new double[N*M]);
        std::copy(obj.data.get(), obj.data.get()+(obj.N*obj.M), data.get());
        stddbg << " copy assignment operator" << std::endl;
    }
    return *this;
}

Matrix& Matrix::operator =(Matrix&& obj) // move assignment operator
{
    if (this != &obj) {
        N = obj.N;
        M = obj.M;
        data = std::move(obj.data);

        obj.N = obj.M = 0;

        stddbg << " move assignment operator" << std::endl;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Matrix& obj)
{
    for (size_t i = 0; i < obj.N; i++) {
        out << "{";
        for (size_t j = 0; j < obj.M; j++) {
            out << obj.data[i*obj.M + j];
            if (j != obj.M - 1) {
                out << ", ";
            }
        }
        out << "}" << std::endl;
    }
    return out;
}

Matrix Matrix::operator -() const
{
    Matrix temp(N, M);
    std::transform(data.get(), data.get()+N*M, temp.data.get(), std::negate<double>());
    return temp;
}

const size_t Matrix::getIndex(const size_t n, const size_t m) const
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


MatrixWithLabel::MatrixWithLabel(std::string label_, size_t N_, size_t M_) :
    Matrix(N_, M_), label(label_)
{}

MatrixWithLabel::MatrixWithLabel(std::string label_, std::initializer_list<std::initializer_list<double>> l) :
    Matrix(l), label(label_)
{}

MatrixWithLabel::MatrixWithLabel(const MatrixWithLabel& obj) : // copy constructor
    Matrix(obj.N, obj.M), label(obj.label)
{
    data.reset(new double[N*M]);
    std::copy(obj.data.get(), obj.data.get()+(obj.N*obj.M), data.get());
    stddbg << " copy constructor (MatrixWithLabel)" << std::endl;
}

void MatrixWithLabel::setLabel(std::string label_)
{
    label = label_;
}

const std::string MatrixWithLabel::getLabel() const
{
    return label;
}

MatrixWithLabel MatrixWithLabel::operator -() const
{
    MatrixWithLabel temp{label, N, M};
    std::transform(data.get(), data.get()+N*M, temp.data.get(), std::negate<double>());
    return temp;
}

// vim: fen
