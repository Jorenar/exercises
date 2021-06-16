// Jakub Łukasiewicz

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "macros.h"
#include "helpers.h"
#include "task_functions.h"

int menu(int *, int *);

int *arr;

int main(int argc, char *argv[])
{
    int option;
    int n = 0; // długość tablicy

    if (argc > 1) {
        n = argc - 1;
        arr = malloc(n * sizeof(*arr));
        for (int i = 0; i < n; ++i)
            arr[i] = atoi(argv[i + 1]);
    }

    srand(time(NULL));

    clear_screen();

    do {
        if (menu(&option, &n) != 1)
            scanf_wrapper("%d", &option, "Wrpowadzono niepoprawną wartość. Wprowadź poprawny nr opcji: ");

        switch(option) {
            case 0:
                free(arr);
                break;
            case 1:
                read_array(&n);
                break;
            case 2:
                element_lottery(&n);
                break;
            case 3:
                find_1st_index(&n);
                break;
            case 4:
                delete_index(&n);
                break;
            case 5:
                insertion_sort(&n);
                print_arr(&n);
                break;
            case 6:
                insert_into_sorted(&n);
                break;
            case 7:
                insert_on_index(&n);
                break;
            case 8:
                binary_search(&n);
                break;
            case 9:
                delete_duplicates(&n);
                break;
            case 10:
                subarray(&n);
                break;
            case 11:
                print_arr(&n);
                break;
            case 12:
                clear_screen();
                printf("\nTablica ma długość " BOLD_NR "\n\n", n);
                break;
            case 13:
                generate_random_array(&n);
                break;
            default:
                clear_screen();
                printf("\nNie ma takiej opcji\n\n");
                break;
        }
    } while (option);

    NL;
    return 0;
}

int menu(int *option, int *n)
{
    int x;
    printf(BOLD "  MENU\n" RESET);
    printf(BOLD "     [0] " RESET "Zakończenie działania programu\n");
    printf(BOLD "     [1] " RESET "Wczytywanie zadanej liczby elementów\n");

    if (*n) { // Those operations cannot be done on empty array
        printf(BOLD "     [2] " RESET "Losowanie zadanej liczby elementów\n");
        printf(BOLD "     [3] " RESET "Wyznaczenie indeksu pierwszego wystąpienia zadanego elementu w tablicy\n");
        printf(BOLD "     [4] " RESET "Usuwanie z tablicy elementu o danym indeksie\n");
        printf(BOLD "     [5] " RESET "Sortowanie przez wstawianie\n");
        printf(BOLD "     [6] " RESET "Wstawianie do tablicy uporządkowanej zadanego elementu zachowując porządek tablicy po wstawieniu (posortuje, jeśli niepostortowana)\n");
        printf(BOLD "     [7] " RESET "Wstawianie do tablicy elementu na podaną pozycję (jeśli indeks będzie mniejszy od 0, bądź większy od rozmiaru tablicy, to element zostanie wstawiony, odpowiednio, na początek, bądź koniec tablicy)\n");
        printf(BOLD "     [8] " RESET "Wyszukiwanie binarne zadanego elementu w tablicy uporządkowanej (posortuje, jeśli niepostortowana)\n");
        printf(BOLD "     [9] " RESET "Usuwanie duplikatów z tablicy\n");
        printf(BOLD "    [10] " RESET "Znajdowanie początku i długości najdłuższej podtablicy posortowanej niemalejąco\n");
        printf(BOLD "    [11] " RESET "Wyświetlenie tablicy\n");
        printf(BOLD "    [12] " RESET "Wyświetlenie długośći tablicy\n");
    }

    printf(BOLD "    [13] " RESET "Wygenerowanie losowej tablicy dwudziestoelementowej\n");

    printf(">> Podaj numer czynności do wykonania: ");

    x = scanf("%d", option);

    while( !*n && *option != 0 && *option != 1  && *option != 13) {
        printf("Nie masz obecnie dostępu do tej opcji lub wprowadziłeś niepoprawną wartość!\n");
        printf( "  Podaj numer czynności do wykonania: ");
        x = scanf_wrapper("%d", option, "Proszę wprowadzić liczbę całkowitą: ");
    }

    return x;
}

// vim: fen
