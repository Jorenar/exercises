#pragma once

#include "matrix.hpp"

class PairOfMatrices {
  public:
    PairOfMatrices(Matrix, Matrix);
    PairOfMatrices(PairOfMatrices&&);
    PairOfMatrices& operator =(PairOfMatrices&&);

    Matrix left;
    Matrix right;
};
