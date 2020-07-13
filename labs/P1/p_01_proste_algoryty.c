// Jakub Łukasiewicz

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void roots_of_equation(double, double, double);
void pseudo_sort(double, double, double);
void prime(int);
int  eukleides(int, int);

int main(int argc, char *argv[])
{
    int option;
    double a, b, c; // Do [1] oraz [2]
    int x, y;       // `x` jest do [3], a `x y` do [4]

    if (argc < 2) {
        printf("Co chcesz zrobić?\n");
        printf("    [1] Obliczyć pierwiastki równania  ax^2 + bx + c = 0\n");
        printf("    [2] Wypisać liczby a, b, c w porządku niemalejącym\n");
        printf("    [3] Sprawdzić, czy dana liczba jest liczbą pierwszą\n");
        printf("    [4] Obliczyć NWD(a, b) – dwa algorytmy Euklidesa\n");
        printf("  Podaj numer opcji: ");

        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Podaj, oddzielone spacją, współczynniki równania: ");
                scanf(" %lf %lf %lf", &a, &b, &c);
                roots_of_equation(a, b, c);
                break;
            case 2:
                printf("Podaj, oddzielone spacją, trzy liczby: ");
                scanf(" %lf %lf %lf", &a, &b, &c);
                pseudo_sort(a, b, c);
                break;
            case 3:
                printf("Podaj liczbę całkowitą: ");
                scanf(" %d", &x);
                prime(x);
                break;
            case 4:
                printf("Podaj, oddzielone spacją, dwie liczby całkowite: ");
                scanf(" %d %d", &x, &y);
                printf("gcd(%d, %d) = %d\n", x, y, eukleides(x, y));
                break;
        }
    } else {
        if (!strcmp(argv[1], "-h")) {
            printf("Program zawiera funkcje interaktywne.\n");
            printf("Jeśli chcesz je pominąć, możesz wybrać opcje:\n");
            printf("    -h       Wyświetlić ten ekran pomocy\n");
            printf("    -1       Obliczyć pierwiastki równania  ax^2 + bx + c = 0\n");
            printf("    -2       Wypisać liczby a, b, c w porządku niemalejącym\n");
            printf("    -3       Sprawdzić, czy dana liczba jest liczbą pierwszą\n");
            printf("    -4       Obliczyć NWD(a, b) – dwa algorytmy Euklidesa\n");
            printf("\n");

        } else if (!strcmp(argv[1], "-1")) {
            if ( argc == 2) {
                a = b = c = 0;
            } else if (argc == 3) {
                a = b = 0;
                c = atof(argv[2]);
            } else if (argc == 4) {
                a = 0;
                b = atof(argv[2]);
                c = atof(argv[3]);
            } else {
                a = atof(argv[2]);
                b = atof(argv[3]);
                c = atof(argv[4]);
            }
            roots_of_equation(a, b, c);

        } else if (!strcmp(argv[1], "-2")) {
            if (argc < 5) {
                printf("Podaj, oddzielone spacją, trzy liczby: ");
                scanf(" %lf %lf %lf", &a, &b, &c);
            } else {
                a = atof(argv[2]);
                b = atof(argv[3]);
                c = atof(argv[4]);
            }
            pseudo_sort(a, b, c);
        } else if (!strcmp(argv[1], "-3")) {
            if (argc == 2) {
                printf("Podaj liczbę całkowitą: ");
                scanf(" %d", &x);
            } else {
                x = atoi(argv[2]);
            }
            prime(x);
        } else if (!strcmp(argv[1], "-4")) {
            if ( argc < 4 ) {
                printf("Podaj, oddzielone spacją, dwie liczby całkowite: ");
                scanf(" %d %d", &x, &y);
            } else {
                x = atoi(argv[2]);
                y = atoi(argv[3]);
            }
            printf("gcd(%d, %d) = %d\n", x, y, eukleides(x, y));
        }
    }

    return 0;
}

void roots_of_equation(double a, double b, double c)
{
    if ( a != 0 ) {
        double d = (b * b) - (4 * a * c);
        if (d >= 0) { // Założenie: domeną są liczby rzeczywiste
            d = sqrt(d);
            double x1 = (-b - d) / (2 * a);
            double x2 = (-b + d) / (2 * a);
            printf("Dwa pierwiastki: %lf, %lf\n", x1, x2);
        } else {
            printf("Brak rozwiązań rzeczywistych\n");
        }
    } else if ( b != 0 ) {
        double x0 = -b / a;
        printf("Jedno rozwiązanie liniowe: %lf\n", x0);
    } else if ( c != 0 ) {
        printf("Brak rozwiązań\n");
    } else {
        printf("Wszystkie liczby rzeczywiste\n");
    }
}

void pseudo_sort(double a, double b, double c)
{
    printf("Liczby %lf, %lf, %lf w kolejności niemalejącej: ", a, b, c);
    if (a <= b && a <= c) {
        printf("%lf ", a);
        if (b <= c)
            printf("%lf %lf\n", b, c);
        else
            printf("%lf %lf\n", c, b);
    } else if (b <= a && b <= c) {
        printf("%lf ", b);
        if (a <= c)
            printf("%lf %lf\n", a, c);
        else
            printf("%lf %lf\n", c, a);
    } else {
        printf("%lf ", c);
        if (a <= b)
            printf("%lf %lf\n", a, b);
        else
            printf("%lf %lf\n", b, a);
    }
}

void prime(int a)
{
    if (a == 0 || a == 1) {
        printf("Liczba %d nie jest liczbą pierwszą\n", a);
    } else {
        int i = 2;

        while(a % i != 0) // wolniej, acz strukturalnie
            i++;

        if (i == a)
            printf("Liczba %d jest liczbą pierwszą\n", a);
        else
            printf("Liczba %d nie jest liczbą pierwszą\n", a);
    }
}

int eukleides(int a, int b)
{
    int temp;
    while (b) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Alternatywna (wolniejsza) werscja algorytmu Euklidesa
/*
int euklides(int a, int b)
{
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
*/
