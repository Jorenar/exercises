#include "pair.hpp"

PairOfMatrices::PairOfMatrices(Matrix A, Matrix B) : left(A), right(B) {}

PairOfMatrices::PairOfMatrices(PairOfMatrices&& obj)
{
    left = std::move(obj.left);
    right = std::move(obj.right);
}

PairOfMatrices& PairOfMatrices::operator =(PairOfMatrices&& obj)
{
    if (this != &obj) {
        left = std::move(obj.left);
        right = std::move(obj.right);
    }
    return *this;
}
