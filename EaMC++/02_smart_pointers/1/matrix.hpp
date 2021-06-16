#pragma once

#include <initializer_list>
#include <memory>
#include <ostream>

class Matrix {
  public:
    Matrix();
    Matrix(size_t, size_t);
    Matrix(std::initializer_list<std::initializer_list<double>>);
    Matrix(const Matrix&);  // copy constructor
    Matrix(Matrix&&);       // move constructor

    ~Matrix() = default;

    double operator ()(size_t, size_t) const;
    double& operator ()(size_t, size_t);

    Matrix& operator =(const Matrix&);  // copy assignment operator
    Matrix& operator =(Matrix&&);       // move assignment operator
    Matrix operator -() const;

    friend std::ostream& operator <<(std::ostream&, const Matrix&);

  protected:
    size_t N; // rows
    size_t M; // columns
    std::unique_ptr<double[]> data;

    const size_t getIndex(const size_t, const size_t) const;
};

class MatrixWithLabel : public Matrix {
  public:
    using Matrix::Matrix;

    MatrixWithLabel(std::string, size_t, size_t);
    MatrixWithLabel(std::string, std::initializer_list<std::initializer_list<double>>);

    MatrixWithLabel(const MatrixWithLabel&); // copy constructor
    MatrixWithLabel(MatrixWithLabel&&) = default;  // move constructor (default)

    MatrixWithLabel& operator =(const MatrixWithLabel&) = default;  // copy assignment operator
    MatrixWithLabel& operator =(MatrixWithLabel&&) = default;       // move assignment operator (default)

    void setLabel(std::string);
    const std::string getLabel() const;

    MatrixWithLabel operator -() const;

  private:
    std::string label;
};
