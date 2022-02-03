// Jakub Lukasiewicz

#include <iostream>

typedef const char c_int8;

const unsigned char N_max = 32;

inline int p2(const int x) { return x * x; }; // x to power of 2

void figures(const long long cube[][::N_max][::N_max], const unsigned short N, const char type,
    const short l, const short v, const short p, const short h, const short w, const short d)
{
    // l,v,p - coordinates of the beginnings
    // h,w,d - dimensions

    long long sum = 0;
    short X, Y, Z; // current point

    bool is_T = type == 'T'; // Is it a pyramid?

    // directions of shift vectors
    c_int8 x = l >= N / 2 ? -1 : 1;
    c_int8 y = v >= N / 2 ? -1 : 1;
    c_int8 z = p >= N / 2 ? -1 : 1;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w - i * is_T; ++j) {
            for (int k = 0; k < d - (i + j)*is_T; ++k) {
                X = l + x * i;
                Y = v + y * j;
                Z = p + z * k;
                if (X < N && Y < N && Z < N && X >= 0 && Y >= 0 && Z >= 0) {
                    sum += cube[X][Y][Z] * (is_T || type == 'C' || p2(X - l) + p2(Y - v) + p2(Z - p) <= p2(h - 1));
                }
            }
        }
    }

    std::cout << sum << std::endl;
}

long long laplace(const long long matrix[][::N_max], const unsigned short N)
{
    if (N == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    }
    else {
        long long det = 0;
        long long submatrix[::N_max][::N_max];
        bool offset = 0;
        for (int X = 0; X < N; X++) {
            if (matrix[0][X]) {
                for (int i = 1; i < N; i++) {
                    offset = 0;
                    for (int j = 0; j < N; j++) {
                        if (j != X) {
                            submatrix[i - 1][j - offset] = matrix[i][j];
                        }
                        else {
                            offset = 1;
                        }
                    }
                }
                det += (X % 2 ? -1 : 1) * matrix[0][X] * laplace(submatrix, N - 1);
            }
        }
        return det;
    }
}

void det(const long long cube[][::N_max][::N_max], const unsigned short N,
    const char K, const unsigned short idx)
{
    if (N == 1) {
        std::cout << cube[0][0][0] << std::endl;
    }
    else {
        long long matrix[::N_max][::N_max];
        const bool x = K == 'l';
        const bool y = K == 'v';
        const bool z = K == 'p';
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                matrix[i][j] = cube[(z ? i : i*y) + idx*x][i*x + j*z + idx*y][(x ? j : j*y) + idx*z];
            }
        }
        std::cout << laplace(matrix, N) << std::endl;
    }
}

int main()
{
    unsigned short N;
    long long cube[::N_max][::N_max][::N_max];
    char code, K;
    short l, v, p, h, w, d;

    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                std::cin >> cube[j][k][i]; // Changed order?!
            }
        }
    }

    std::cin >> code;
    while (code != 'E') {
        if (code == 'D') {
            std::cin >> K >> l;
            det(cube, N, K, l);
        }
        else {
            std::cin >> l >> v >> p >> h;

            if (code == 'C') {
                std::cin >> w >> d;
                h++;
                w++;
                d++; // correction of values
            }
            else {
                w = d = ++h;
            }

            figures(cube, N, code, l, v, p, h, w, d);
        }
        std::cin >> code;
    }

    return 0;
}

// vim: fen
