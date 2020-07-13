#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task_functions.h"
#include "helpers.h"
#include "macros.h"

extern int *arr;

void read_array(int *n)
{
    printf("\n>>> Podaj, jak długa będzie tablica: ");
    //if (scanf("%d", n) != 1)
    scanf_wrapper("%d", n, "Proszę wprowadzić liczbę całkowitą: ");
    arr = realloc(arr, *n * sizeof(*arr));
    for (int i = 0; i < *n; ++i) {
        printf(">>>> Podaj wartość elementu nr %d: ", i + 1);
        if (scanf("%d", arr + i) != 1 )
            scanf_wrapper("%d", arr + i, "Proszę wprowadzić liczbę całkowitą: ");
    }
    print_arr(n);
}

void element_lottery(int *n)
{
    int x;
    printf("\n>>> Podaj, ile elementów chcesz wylosować: ");
    scanf_wrapper("%d", &x, "Podaj liczbę całkowitą: ");
    clear_screen();
    printf("\nWylosowane elementy: ");
    for (int i = 0; i < x; ++i)
        printf(BOLD_NR " ", arr[rand() % *n]);
    printf("\n\n");
}

void find_1st_index(int *n)
{
    int el;

    printf("\n>>> Podaj element, który chcesz wyszukać: ");
    scanf_wrapper("%d", &el, "Podaj liczbę całkowitą: ");

    int i = 0;

    while (arr[i] != el && i < *n)
        ++i;

    clear_screen();

    NL;
    if (i == *n)
        printf(BOLD_NR " nie znajduje się w tablicy", el);
    else
        printf("Pierwsze wystąpienie wartości " BOLD_NR " ma indeks " BOLD_NR " w tablicy", el, i);

    printf("\n\n");
}

void delete_index(int *n)
{
    int idx;
    printf("\n>>> Podaj indeks, spod którego chcesz usunąć element: ");
    scanf_wrapper("%d", &idx, "L c");

    int flag = 0;
    for (int i = 0; i < *n; ++i) {
        if (i == idx)
            flag = 1;
        if (flag && i + 1 < *n)
            arr[i] = arr[i + 1];
    }
    resize_array(*n - 1, n);

    print_arr(n);
}

void insertion_sort(int *n)
{
    int i, j, k;
    for (i = 1; i < *n; i++) {
        k = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = k;
    }
}

void insert_into_sorted(int *n)
{
    int el;

    printf("\n>>> Podaj element, który chcesz wstawić: ");
    scanf_wrapper("%d", &el, "Podaj liczbę całkowitą: ");

    int i = *n - 1;

    int how_sorted = is_sorted(n);

    if (how_sorted) {
        resize_array(*n + 1, n);
        while (((el < arr[i] && how_sorted == 1) || (el > arr[i] && how_sorted == -1)) && i >= 0) {
            arr[i + 1] = arr[i];
            i--;
        }
    } else {
        insertion_sort(n);
        resize_array(*n + 1, n);
        while (el < arr[i] && i >= 0) { // Jedyna różnica, to znak nierówności
            arr[i + 1] = arr[i];
            i--;
        }
    }

    arr[i + 1] = el;

    print_arr(n);
}

void insert_on_index(int *n)
{
    int el, idx;

    printf("\n>>> Podaj element, który chcesz wstawić: ");
    scanf_wrapper("%d", &el, "Podaj liczbę całkowitą: ");

    printf(">>> Podaj indeks, na który chcesz wstawić: ");
    scanf_wrapper("%d", &idx, "Podaj liczbę całkowitą: ");

    resize_array(*n + 1, n);
    int i = *n - 1;
    while ( i > 0 && i > idx) {
        arr[i] = arr[i - 1];
        i--;
    }

    arr[i] = el;

    print_arr(n);
}

void binary_search(int *n)
{
    int el;

    printf("\n>>> Podaj element, który chcesz wyszukać: ");
    scanf_wrapper("%d", &el, "Podaj liczbę całkowitą: ");

    if (is_sorted(n) != 1)
        insertion_sort(n);

    clear_screen();

    if (el < arr[0] || el > arr[*n - 1]) {
        printf("\nElement nie znajduje się w tablicy\n\n");
    } else {

        int x = *n / 2;

        while (arr[x] != el) {
            if (el > arr[x])
                x += (*n - x) / 2;
            else
                x /= 2;
        }

        while (arr[x - 1] == el)
            x--;

        printf("\nElement o wartości " BOLD_NR " znajduje się na pozycji " BOLD_NR "\n\n", el, x);
    }
}

void delete_duplicates(int *n)
{
    int k;
    int m = 0;

    for (int i = 0; i < *n - m; ++i) {
        for (int j = i + 1; j < *n - m; ++j) {
            if (arr[i] == arr[j]) {
                k = j;
                m++;
                while(k < *n - m) {
                    arr[k] = arr[k + 1];
                    k++;
                }
            }
        }
    }

    resize_array(*n - m, n);

    print_arr(n);
}

void subarray(int *n)
{
    clear_screen();

    if (is_sorted(n) == 1) {
        printf("\nCała tablica jest posortowana niemalejąco\n\n");
    } else {
        int start = 0;
        int size = 1;
        int start_temp = 0;
        int size_temp = 1;

        for (int i = 0; i < *n; ++i) {
            if (arr[i] > arr[i + 1]) {
                if (size_temp > size) {
                    start = start_temp;
                    size = size_temp;
                }
                start_temp = i + 1;
                size_temp = 1;
            } else {
                size_temp++;
            }
        }

        printf("\nNajdłuższa posortowana niemalejąco podtablica zaczyna się na indeksie " BOLD_NR " i ma długość " BOLD_NR "\n\n", start, size);
    }
}

// vim: fen
