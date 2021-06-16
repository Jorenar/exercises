#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef unix
    #include <unistd.h>
    #define SEED getpid() + time(NULL)
#else
    #define SEED time(NULL)
#endif

#define ARRAY_N 1000

void swap(int [], int, int);
int median(int [], int, int);
int left(int [], int, int);
void quickSort(int [], int, int, int (*)(int [], int, int));
void printArray(int [], int);

int main()
{
    srand(SEED);

    int n = ARRAY_N;
    int array[ARRAY_N];
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100 + 1;
    }
    int* arr = malloc(n * sizeof(*arr));

    clock_t start;
    clock_t end;

    memcpy(arr, array, n * sizeof(*array));
    start = clock();
    quickSort(arr, 0, n-1, left);
    end = clock();
    printf("left:   %d\n", end - start);

    memcpy(arr, array, n * sizeof(*array));
    start = clock();
    quickSort(arr, 0, n-1, median);
    end = clock();
    printf("median: %d\n", end - start);

    free(arr);
    return 0;
}

/* RESULTS:
 *  n = 100
 *    left:   10
 *    median: 10
 *
 *    left:   11
 *    median: 10
 *
 *  n = 10000
 *    left:   1709
 *    median: 1541
 *
 *    left:   1681
 *    median: 1565
 *
 *  n = 1000000
 *    left:   3190169
 *    median: 2914469
 *
 *    left:   3191781
 *    median: 2926509
 */

void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int median(int arr[], int L, int R)
{
    int m = (L + R)/2;

    if (arr[m] > arr[L]) {
        swap(arr, L, m);
    }

    if (arr[L] > arr[R]) {
        swap(arr, L, R);
    }

    if (arr[m] > arr[R]) {
        swap(arr, m, R);
    }

    int pivot = arr[L];
    int i = R;

    for (int j = R; j >= L + 1; --j) {
        if (arr[j] >= pivot) {
            swap(arr, i, j);
            --i;
        }
    }

    swap(arr, i, L);

    return i;
}

int left(int arr[], int L, int R)
{
    int pivot = arr[L];
    int i = R;

    for (int j = R; j >= L + 1; --j) {
        if (arr[j] >= pivot) {
            swap(arr, i, j);
            --i;
        }
    }

    swap(arr, i, L);

    return i;
}

void quickSort(int arr[], int L, int R, int (*partition)(int [], int, int))
{
    if (L < R) {
        int q = partition(arr, L, R);
        quickSort(arr, L, q, partition);
        quickSort(arr, q + 1, R, partition);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// vim: fen
