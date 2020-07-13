// Jakub Lukasiewicz

#include <iostream>

void Add(int, int []);
void Create(int n, int [], int []);
void Union(int [], int [], int []);
void Intersection(int [], int [], int []);
void Difference(int [], int [], int []);
void Symmetric(int [], int [], int []);
void Complement(int [], int []);

bool Subset(int [], int []);
bool Equal(int [], int []);
bool Empty(int []);
bool Nonempty(int []);
bool Element(int, int []);

double Arithmetic(int []);
double Harmonic(int []);

void MinMax(int [], int*, int&);
void Cardinality(int [], int*);
void Properties(int [], const char*, double&, double*, int&, int*, int&);

const short U_MAX = 4095;
const short U_MIN = 1;

void Add(int x, int A[])
{
    if (x >= U_MIN && x <= U_MAX ) {
        int N = 0;
        while (A[N] != -1) { N++; }

        if ( ! Element(x, A) ) {
            A[N + 1] = A[N];
            A[N] = x;
        }
    }
}

void Create(int n, int arr[], int A[])
{
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if ( ! Element(arr[i], A) && arr[i] >= U_MIN && arr[i] <= U_MAX ) {
            A[j++] = arr[i];
        }
    }
    A[j] = -1;
}

void Union(int A[], int B[], int AuB[])
{
    int j = 0;

    for (int i = 0; A[i] != -1; ++i) {
        if ( !Element(A[i], B) ) {
            AuB[j++] = A[i];
        }
    }

    for (int i = 0; B[i] != -1; ++i) {
        AuB[j++] = B[i];
    }

    AuB[j] = -1;
}

void Intersection(int A[], int B[], int AnB[])
{
    int j = 0;

    for (int i = 0; A[i] != -1; ++i) {
        if ( Element(A[i], B) ) {
            AnB[j++] = A[i];
        }
    }

    AnB[j] = -1;
}

void Difference(int A[], int B[], int C[]) // C equals A\B
{
    int j = 0;

    for (int i = 0; A[i] != -1; ++i) {
        if ( !Element(A[i], B) ) {
            C[j++] = A[i];
        }
    }

    C[j] = -1;
}

void Symmetric(int A[], int B[], int C[]) // C equals A⊖B
{
    int j = 0;

    for (int i = 0; A[i] != -1; ++i) {
        if ( !Element(A[i], B) ) {
            C[j++] = A[i];
        }
    }

    for (int i = 0; B[i] != -1; ++i) {
        if ( !Element(B[i], A) ) {
            C[j++] = B[i];
        }
    }

    C[j] = -1;

}

void Complement(int A[], int Ac[])
{
    int j = 0;
    for (int i = U_MIN; i <= U_MAX; ++i) {
        if (!Element(i, A)) {
            Ac[j++] = i;
        }
    }
    Ac[j] = -1;
}

bool Subset(int A[], int U[])
{
    for (int i = 0; A[i] != -1; ++i) {
        if (! Element(A[i], U) ) {
            return false;
        }
    }
    return true;
}

bool Equal(int A[], int B[])
{
    if ( Subset(A, B) && Subset(B, A) ) {
        return true;
    }
    return false;
}

bool Empty(int A[])
{
    return A[0] == -1;
}

bool Nonempty(int A[])
{
    return A[0] != -1;
}

bool Element(int x, int A[])
{
    if (x < U_MIN || x > U_MAX ) {
        return false;
    }

    for (int i = 0; A[i] != -1; ++i) {
        if (x == A[i]) {
            return true;
        }
    }

    return false;
}

double Arithmetic(int A[])
{
    if (Empty(A)) {
        return 0;
    }

    double sum = 0;

    int i = 0;
    while (A[i] != -1) {
        sum += A[i++];
    }

    return sum/i;
}

double Harmonic(int A[])
{
    if (Empty(A)) {
        return 1;
    }

    double sum_of_inv = 0;

    int i = 0;
    while (A[i] != -1) {
        sum_of_inv += double(1)/A[i++];
    }

    return i/sum_of_inv;
}

void MinMax(int A[], int* A_min, int& A_max)
{
    if (Nonempty(A)) {
        *A_min = U_MAX;
        A_max = U_MIN;

        for (int i = 0; A[i] != -1; ++i) {
            if (A[i] < *A_min) {
                *A_min = A[i];
            }
            if (A[i] > A_max) {
                A_max = A[i];
            }
        }

    }
}

void Cardinality(int A[], int* N) // N = #A
{
    *N = 0;
    while (A[*N] != -1 ) { (*N)++; }
}

void Properties(int A[], char* operations, double& avg_Arithmetic,
    double* avg_Harmonic, int& A_min, int* A_max, int& N)
{
    for (char* opr = operations; *opr; ++opr) {
        if (*opr == 'a') {
            avg_Arithmetic = Arithmetic(A);
        }
        else if (*opr == 'h') {
            *avg_Harmonic = Harmonic(A);
        }
        else if (*opr == 'm') {
            MinMax(A, &A_min, *A_max);
        }
        else if (*opr == 'c') {
            Cardinality(A, &N);
        }
    }
}

// vim: fen
