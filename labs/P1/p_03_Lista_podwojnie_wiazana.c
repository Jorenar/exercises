/* Jakub Łukasiewicz */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void makeNull();
void displayForward();
void displayBackward();
void insertFirst(long);
void insertLast(long);
void insertAfter(long, long);
void deleteFirst();
void deleteLast();
void deleteKey(long);
void locate(long);

typedef struct DLink_t DLink;

void  menu(long*);
int   readValues(const char*, const char*, void (*)(), const char*, ...);
void  newNode(long, DLink*, DLink*);
_Bool isKey(long);

#ifdef __unix__
    #define RESET    "\033[0m"
    #define BOLD     "\033[1m"
    #define BOLD_NR  "\033[1m%d\033[0m"
    #define ERR_MSG  "\033[31mPodaj liczbę całkowitą: \033[0m"
#else
    #define RESET    ""
    #define BOLD     ""
    #define BOLD_NR  "%d"
    #define ERR_MSG  "Podaj liczbe calkowita: "
#endif

struct DLink_t {
    long info;
    struct DLink_t* next;
    struct DLink_t* prev;
};

DLink* First = NULL;
DLink* Last = NULL;

int main()
{
    int option;
    long x;
    long key;

    do {
        menu((long*)&option);
        system("cls||clear");
        switch (option) {
            case 0:
            case 1:
                makeNull();
                break;
            case 2:
                displayForward();
                break;
            case 3:
                displayBackward();
                break;
            case 4:
                readValues("\n>>> Podaj element, ktory chcesz wstawic: ", ERR_MSG, makeNull, "%ld", &x);
                insertFirst(x);
                printf("\n");
                break;
            case 5:
                readValues("\n>>> Podaj element, ktory chcesz wstawic: ", ERR_MSG, makeNull, "%ld", &x);
                insertLast(x);
                printf("\n");
                break;
            case 6:
                readValues("\n>>> Podaj element, ktory chcesz wstawic: ", ERR_MSG, makeNull, "%ld", &x);
                readValues(">>> Podaj klucz, po ktorym chcesz wstawic: ", ERR_MSG, makeNull, "%ld", &key);
                insertAfter(x, key);
                printf("\n");
                break;
            case 7:
                deleteFirst();
                break;
            case 8:
                deleteLast();
                break;
            case 9:
                readValues("\n>>> Podaj klucz, ktory chcesz usunac: ", ERR_MSG, makeNull, "%ld", &key);
                deleteKey(key);
                printf("\n");
                break;
            case 10:
                readValues("\n>>> Podaj klucz, ktory chcesz zlokalizowac: ", ERR_MSG, makeNull, "%ld", &key);
                locate(key);
                break;
            case 11:
                system("cls||clear");
                break;
            default:
                printf("\nNie ma takiej opcji\n\n");
                break;
        }
    } while (option);

    return 0;
}


void menu(long* option)
{
    printf(BOLD "  MENU\n" RESET);
    printf(BOLD "     [0] " RESET "Zakończenie dzialania programu\n");
    printf(BOLD "     [1] " RESET "Pusta lista\n");
    printf(BOLD "     [2] " RESET "Wypisanie elementow listy od poczatku do konca\n");
    printf(BOLD "     [3] " RESET "Wypisanie elementow listy od konca do poczatku\n");
    printf(BOLD "     [4] " RESET "Wstawienie elementu na poczatek listy\n");
    printf(BOLD "     [5] " RESET "Wstawienie elementu na koniec listy\n");

    if (First) { /* Those operations cannot be done on empty list */
        printf(BOLD "     [6] " RESET "Wstawienie elementu po okreslonym kluczu\n");
        printf(BOLD "     [7] " RESET "Usuniecie pierwszego elementu\n");
        printf(BOLD "     [8] " RESET "Usuniecie ostatniego elementu\n");
        printf(BOLD "     [9] " RESET "Usuniecie elementu o okreslonym kluczu\n");
        printf(BOLD "    [10] " RESET "Wyszukanie pozycji zadanego klucza (numeracja od 1)\n");
    }

    printf(BOLD "    [11] " RESET "Wyczyszczenie ekranu\n");

    readValues(">> Podaj numer czynnosci do wykonania: ", ERR_MSG, makeNull, "%ld", option);

    while (!First && *option >= 6 && *option <= 10) {
        readValues("Nie masz obecnie dostepu do tej opcji\n  Podaj numer czynnosci: ", ERR_MSG, makeNull, "%ld", option);
    }
}

int readValues(const char* prompt, const char* errMsg,
    void (*eofFunc)(), const char* fmt, ...)
{
    int n = 0;
    va_list vars;
    va_start(vars, fmt);

    int i;
    for (i = 0; fmt[i]; ++i) {
        if (fmt[i] == '%') {
            n++;
        }
    }

    puts(prompt);

    int flag = vscanf(fmt, vars);
    while (flag != n && flag != EOF) {
        getchar();
        fputs(errMsg, stderr);
        flag = vscanf(fmt, vars);
    }

    va_end(vars);

    if (flag == EOF) {
        eofFunc();
        putchar('\n');
        exit(0);
    }

    return flag;
}

_Bool isKey(long key)
{
    DLink* pos = First;

    while (pos && pos->info != key) {
        pos = pos->next;
    }

    return pos;
}

void newNode(long x, DLink* prevNode, DLink* nextNode)
{
    DLink* node = malloc(sizeof(*node));
    node->info = x;
    node->prev = prevNode;
    node->next = nextNode;
    if (prevNode) {
        prevNode->next = node;
    }
    if (nextNode) {
        nextNode->prev = node;
    }
    if (nextNode == First) {
        First = node;
    }
    if (prevNode == Last) {
        Last = node;
    }
}


void makeNull()
{
    DLink* pos = Last;
    DLink* temp;
    while (pos) {
        temp = pos->prev;
        free(pos);
        pos = temp;
    }
    First = Last = NULL;
}

void displayForward()
{
    DLink* pos = First;
    printf("\nLista: [ ");
    while (pos) {
        printf("%ld", pos->info);
        pos = pos->next;
        if (pos) { printf(", "); }
    }
    printf(" ]\n\n");
}

void displayBackward()
{
    DLink* pos = Last;
    printf("\nLista: [ ");
    while (pos) {
        printf("%ld", pos->info);
        pos = pos->prev;
        if (pos) { printf(", "); }
    }
    printf(" ]\n\n");
}

void insertFirst(long x)
{
    if (!isKey(x)) {
        newNode(x, NULL, First);
    } else {
        printf("Istnieje juz element o podanej wartosci\n");
    }
}

void insertLast(long x)
{
    newNode(x, Last, NULL);
}

void insertAfter(long x, long key)
{
    DLink* pos = First;

    while (pos && pos->info != key) {
        pos = pos->next;
    }

    if (pos) {
        newNode(x, pos, pos->next);
        if (pos == Last) {
            Last =  pos->next;
        }
    } else {
        fprintf(stderr, "Brak klucza %ld\n\n", key);
    }
}

void deleteFirst()
{
    if (First == Last) {
        Last = NULL;
    } else {
        First->next->prev = NULL;
    }

    DLink* temp = First;
    First = First->next;
    free(temp);
}

void deleteLast()
{
    if (Last == First) {
        First = NULL;
    } else {
        Last->prev->next = NULL;
    }

    DLink* temp = Last;
    Last = Last->prev;
    free(temp);
}

void deleteKey(long key)
{
    DLink* pos = First;
    while (pos && pos->info != key) {
        pos = pos->next;
    }

    if (pos) {
        DLink* prevNode = pos->prev;
        DLink* nextNode = pos->next;

        if (pos == First) {
            First = nextNode;
        } else {
            prevNode->next = nextNode;
        }

        if (pos == Last) {
            Last = prevNode;
        } else {
            nextNode->prev = prevNode;
        }

        free(pos);

    } else {
        fprintf(stderr, "Brak klucza w liscie\n\n");
    }
}

void locate(long key)
{
    int i = 1;
    DLink* pos = First;
    while (pos && pos->info != key) {
        pos = pos->next;
        i++;
    }

    if (pos) {
        printf("Klucz jest elementem nr %d\n\n", i);
    } else {
        printf("Klucz nie wystepuje w liscie\n\n");
    }
}
