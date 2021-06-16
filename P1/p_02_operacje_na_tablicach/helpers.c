#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"
#include "macros.h"

extern int *arr;

int scanf_wrapper(const char *format, int *variable, const char *msg)
{
    int flag = scanf(format, variable);
    while (flag != 1) {
        if(flag == EOF) {
            NL;
            exit(0);
        }
        getchar();
        fprintf(stderr, RED);
        fprintf(stderr, msg);
        fprintf(stderr, RESET);
        flag = scanf("%d", variable);
    }
    return flag;
}

void print_arr(int *n)
{
    clear_screen();
    printf("\nTablica: ");
    for (int i = 0; i < *n; ++i)
        printf(BOLD_NR " ", arr[i]);
    printf("\n\n");
}

int is_sorted(int *n)
{
    int i = 0;

    while(arr[i] <= arr[i + 1] && i < *n - 1)
        i++;

    if (i == *n - 1) {
        return 1;
    } else {
        i = 0;
        while(arr[i] >= arr[i + 1] && i < *n - 1)
            i++;

        if (i == *n - 1)
            return -1;
        else
            return 0;
    }
}

void resize_array(int size, int *n)
{
    int *arr_copy = malloc(*n * sizeof(*arr_copy));

    for (int i = 0; i < *n; ++i)
        arr_copy[i] = arr[i];

    arr = realloc(arr, size * sizeof(arr));

    if (size < *n) {
        for (int i = 0; i < size; ++i)
            arr[i] = arr_copy[i];
    } else {
        for (int i = 0; i < *n; ++i)
            arr[i] = arr_copy[i];
    }

    free(arr_copy);

    *n = size;
}

void clear_screen()
{
    system("cls||clear");
}

void generate_random_array(int *n)
{
    *n = 20;
    arr = realloc(arr, *n * sizeof(*arr));
    for (int i = 0; i < *n; ++i)
        arr[i] = rand() % 100;
    print_arr(n);
}

// vim: fen
