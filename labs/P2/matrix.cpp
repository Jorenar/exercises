#include "foo.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>

double random_double(double min, double max)
{
    double precision = 3;
    return static_cast<double>(((rand()%(static_cast<int>(std::pow(10,precision)*(max - min) + 1))) + min*std::pow(10,precision)))/std::pow(10,precision);
}


Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}

Matrix::Matrix(size_t rows_, size_t cols_) : rows(rows_), cols(cols_), values(new double[rows*cols] {0}) {}

Matrix::~Matrix()
{
    delete [] values;
}

void Matrix::print()
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << values[i*cols + j] << " ";
        }
        std::cout << std::endl;
    }
}


Matrix* random_matrix(int rows, int cols)
{
    Matrix* temp = new Matrix(rows, cols);
    for (size_t i = 0; i < cols*rows; i++) {
        temp->values[i] = random_double(0, 10);
    }
    return temp;
}


double square(double x)
{
    return x*x;
}

double cube(double x)
{
    return x*x*x;
}


void apply(double (*f)(double), Matrix* mat)
{
    size_t N = (mat->rows)*(mat->cols);
    for (size_t i = 0; i < N; i++) {
        mat->values[i] = f(mat->values[i]);
    }
}

// vim: fen
