#include <cstddef>

double random_double(double, double);

struct Matrix {
    Matrix();
    Matrix(size_t, size_t);
    ~Matrix();
    void print();

    size_t rows;
    size_t cols;
    double* values;
};

Matrix* random_matrix(int, int);

double square(double);
double cube(double);


void apply(double (*f)(double), Matrix*);
