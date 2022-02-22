#include <iostream>
#include <iomanip>

template<typename T, std::size_t N_max>
long long laplace(const T matrix[][N_max], const std::size_t N)
{
    if (N == 1) {
        return matrix[0][0];
    }

    if (N == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    }

    long long det = 0;
    T submatrix[N_max][N_max];
    bool offset = 0;
    for (std::size_t X = 0; X < N; ++X) {
        if (!matrix[0][X]) {
            continue;
        }

        for (std::size_t i = 1; i < N; ++i) {
            offset = 0;
            for (std::size_t j = 0; j < N; ++j) {
                if (j != X) {
                    submatrix[i - 1][j - offset] = matrix[i][j];
                }
                else {
                    offset = 1;
                }
            }
        }
        det += (X % 2 ? -1 : 1) * matrix[0][X] * laplace(submatrix, N-1);
    }
    return det;
}

int main()
{
    int m0[][1] = { { 5 } };                                         //   5
    int m1[][2] = { {3, 7}, {1, -4} };                               // -19
    int m2[][3] = { {1,0,0}, {0, 1, 0}, {0,0,1} };                   //   1
    int m3[][3] = { {-2,-1,2}, {2,1,4}, {-3,3,-1} };                 //  54
    int m4[][3] = { {9,8,7}, {3,4,7}, {0,2,4} };                     // -36
    int m5[][4] = { {1,3,0,-1}, {0,2,1,3}, {3,1,2,1}, {-1,2,0,5} };  //  38

    std::cout << std::setw(4) << laplace(m0, 1) << std::endl;
    std::cout << std::setw(4) << laplace(m1, 2) << std::endl;
    std::cout << std::setw(4) << laplace(m2, 3) << std::endl;
    std::cout << std::setw(4) << laplace(m3, 3) << std::endl;
    std::cout << std::setw(4) << laplace(m4, 3) << std::endl;
    std::cout << std::setw(4) << laplace(m5, 4) << std::endl;

    return 0;
}
