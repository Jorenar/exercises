#include <stdio.h>
#include <math.h>

#define N 500
#define F 6

int drop(int i)
{
    return i == F;
}

int main()
{
    int root = sqrt(N);

    int i = 0;
    int j = 0;

    int r = 0; // drop counter

    while ((++r, i) != F && i < N) {
        j = i;
        i += root;
    }

    if (i < N) {
        i = j;
        while ((++r, i) != F) {
            ++i;
        }
    }

    printf("N          %d\n", N);
    printf("2*sqrt(N)  %d\n", 2*root);
    printf("F          %d\n", i);
    printf("drops      %d\n", r);

    return 0;
}
