// Jakub Lukasiewicz

/* -std=gnu89 */

#include <stdio.h>
#include <stdlib.h>

#define ELEM(A,i,j)   (*(*(A+i+1)+j+1))
#define ROW(A,i)      (*(A+i+1))
#define LEN(A)        (**A)
#define ROW_LEN(A,i)  (**(A+i+1))

typedef int** (*operation_t)(int**);

int** initialize();
int cmpStr(const char*, const char*);
int maxRow(int**);
operation_t decode(const char*);
void swap(int*, int*);
void swapPtr(int**, int**);
int* readRow(int);
int** rowToBlock(int*);

int*  removeElement(int*, int);
int** insertRow(int**, int*, int, int);
int** insertBlock(int**, int**, int, int);

int* insertElement(int*, int, int);
int** removeRow(int**, int);
int** removeBlock(int**, int, int, int, int);

int** afr(int**);
int** alr(int**);
int** afc(int**);
int** alc(int**);
int** ibr(int**);
int** iar(int**);
int** ibc(int**);
int** iac(int**);
int** swr(int**);
int** swc(int**);
int** dfr(int**);
int** dlr(int**);
int** dfc(int**);
int** dlc(int**);
int** rmr(int**);
int** rmc(int**);
int** isb(int**);
int** rmb(int**);
int** prt(int**);
int** end(int**);


int main()
{
    int** thing = initialize();

    char* code  = malloc(4);

    operation_t operation;

    do {
        scanf("%s", code);
        operation = decode(code);
        thing = operation(thing);
    } while (operation != end);

    free(code);

    return 0;
}


int** initialize()
{
    int** thing = malloc(1 * sizeof(*thing));
    *(thing+0)  = malloc(1 * sizeof(**thing));
    LEN(thing)  = 0;
    return thing;
}

int cmpStr(const char* a, const char* b)
{
    int i;
    for (i = 0; i < 3; ++i) {
        if (*(a+i) != *(b+i)) {
            return 0;
        }
    }
    return 1;
}

int maxRow(int** thing)
{
    int max = 0;
    int i;
    for (i = 0; i < LEN(thing); ++i) {
        if (ROW_LEN(thing,i) > max) {
            max = ROW_LEN(thing,i);
        }
    }
    return max;
}

operation_t decode(const char* c)
{
    if (cmpStr("AFR", c)) { return afr; }
    if (cmpStr("ALR", c)) { return alr; }
    if (cmpStr("AFC", c)) { return afc; }
    if (cmpStr("ALC", c)) { return alc; }
    if (cmpStr("IBR", c)) { return ibr; }
    if (cmpStr("IAR", c)) { return iar; }
    if (cmpStr("IBC", c)) { return ibc; }
    if (cmpStr("IAC", c)) { return iac; }
    if (cmpStr("SWR", c)) { return swr; }
    if (cmpStr("SWC", c)) { return swc; }
    if (cmpStr("DFR", c)) { return dfr; }
    if (cmpStr("DLR", c)) { return dlr; }
    if (cmpStr("DFC", c)) { return dfc; }
    if (cmpStr("DLC", c)) { return dlc; }
    if (cmpStr("RMR", c)) { return rmr; }
    if (cmpStr("RMC", c)) { return rmc; }
    if (cmpStr("ISB", c)) { return isb; }
    if (cmpStr("RMB", c)) { return rmb; }
    if (cmpStr("PRT", c)) { return prt; }
    return end;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapPtr(int** a, int** b)
{
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int* readRow(int n)
{
    int* temp = malloc((n+1) * sizeof(*temp));
    *temp = n;
    int i;
    for (i = 0; i < n; ++i) {
        scanf(" %d", temp+i+1);
    }
    return temp;
}

int** rowToBlock(int* row)
{
    int** block = initialize();
    int* r;
    int i;
    for (i = *row - 1; i >= 0; --i) {
        r = malloc(2 * sizeof(*r));
        *(r+0) = 1;
        *(r+1) = *(row+i+1);
        block = insertRow(block, r, 0, 1);
    }
    return block;
}

int** insertRow(int** thing, int* row, int r, int append)
{
    int n = LEN(thing);
    if (r < n || (r == n && append)) {
        thing = realloc(thing, (n+2) * sizeof(*thing));
        int i = n;
        while (i > r) {
            swapPtr(&ROW(thing,i), &ROW(thing,i-1));
            --i;
        }
        ROW(thing,i) = row;
        ++LEN(thing);
    }
    return thing;
}

int** removeRow(int** thing, int r)
{
    int n = LEN(thing);
    if (r < n && n > 0) {
        int i = r;
        while (i < n-1) {
            swapPtr(&ROW(thing,i), &ROW(thing,i+1));
            i++;
        }
        free(ROW(thing,i));
        --LEN(thing);
        return realloc(thing, n * sizeof(*thing)); /* (n+1) - 1 = n */
    } else {
        return thing;
    }
}

int* insertElement(int* row, int c, int x)
{
    int n = *row;
    if (c >= n) {
        c = n;
    }
    row = realloc(row, (n+2) * sizeof(*row));
    int i = n;
    while (i > c) {
        swap(row+i+1, row+i);
        --i;
    }
    *(row+i+1) = x;
    ++(*row);
    return row;
}

int* removeElement(int* row, int c)
{
    if (c < *row) {
        while (c < *row - 1) {
            swap(row+c+1, row+c+2);
            ++c;
        }
        --(*row);
        return realloc(row, (*row + 1) * sizeof(*row));
    } else {
        return row;
    }
}

int** insertBlock(int** thing, int** block, int r, int c)
{
    int h = LEN(block);
    int n = LEN(thing);
    int w;
    int i = 0;
    int j;

    while (i < h && i < n-r) {
        w = ROW_LEN(block, i);
        for (j = 0; j < w; ++j) {
            ROW(thing,r+i) = insertElement(ROW(thing,r+i), c+j, ELEM(block, i, j)); /* room for optimization */
        }
        free(ROW(block, i));
        ++i;
    }

    while (i < h) {
        thing = insertRow(thing, ROW(block, i), LEN(thing), 1);
        ++i;
    }

    free(*block);
    free(block);

    return thing;
}

int** removeBlock(int** thing, int r, int h, int c, int w)
{
    int i = r;
    int j;

    while (i < r+h && i < LEN(thing)) {
        if (c != 0 || ROW_LEN(thing, i) > w) {
            for (j = 0; j < w; ++j) {
                ROW(thing, i) = removeElement(ROW(thing, i), c);
            }
            ++i;
        } else {
            thing = removeRow(thing, i);
            --h;
        }
    }

    return thing;
}


int** afr(int** thing) /* add first row */
{
    int n;
    scanf(" %d", &n);
    int* t = readRow(n);
    return insertRow(thing, t, 0, 1);
}

int** alr(int** thing) /* add last row */
{
    int n;
    scanf(" %d", &n);
    int* t = readRow(n);
    return insertRow(thing, t, LEN(thing), 1);
}

int** afc(int** thing) /* add first column */
{
    int n;
    scanf(" %d", &n);
    int* t = readRow(n);
    int** c = rowToBlock(t);
    free(t);
    return insertBlock(thing, c, 0, 0);
}

int** alc(int** thing) /* append rows */
{
    int h;
    scanf(" %d", &h);
    int* t = readRow(h);
    int** col = rowToBlock(t);
    free(t);
    return insertBlock(thing, col, 0, maxRow(thing));
}

int** ibr(int** thing) /* insert before row */
{
    int r;
    int w;
    scanf(" %d %d", &r, &w);
    int* t = readRow(w);
    return insertRow(thing, t, r, 0);
}

int** iar(int** thing) /* insert after row */
{
    int r;
    int n;
    scanf(" %d %d", &r, &n);
    int* t = readRow(n);
    return insertRow(thing, t, r+1, 1);
}

int** ibc(int** thing) /* insert before column */
{
    int c;
    int h;
    scanf(" %d %d", &c, &h);
    int* t = readRow(h);
    int** col = rowToBlock(t);
    free(t);
    return insertBlock(thing, col, 0, c);
}

int** iac(int** thing) /* insert after column */
{
    int c;
    int h;
    scanf(" %d %d", &c, &h);
    int* t = readRow(h);
    int** col = rowToBlock(t);
    free(t);
    return insertBlock(thing, col, 0, c+1);
}

int** swr(int** thing) /* swap rows */
{
    int r;
    int s;
    scanf(" %d %d", &r, &s);
    if (r < LEN(thing) && s < LEN(thing)) {
        swapPtr(&ROW(thing,r), &ROW(thing,s));
    }
    return thing;
}

int** swc(int** thing) /* swap columns */
{
    int c;
    int d;
    scanf(" %d %d", &c, &d);
    int i;
    for (i = 0; i < LEN(thing); ++i) {
        if (c < ROW_LEN(thing,i) && d < ROW_LEN(thing,i)) {
            swap(&ELEM(thing, i, c), &ELEM(thing, i, d));
        }
    }
    return thing;
}

int** dfr(int** thing) /* delete first row */
{
    return removeRow(thing, 0);
}

int** dlr(int** thing) /* delete last row */
{
    return removeRow(thing, LEN(thing) - 1);
}

int** dfc(int** thing) /* delete first column */
{
    return removeBlock(thing, 0, LEN(thing), 0, 1);
}

int** dlc(int** thing) /* delete last elements */
{
    int i = 0;
    while (i < LEN(thing)) {
        if (ROW_LEN(thing,i) > 1) {
            ROW(thing,i) = removeElement(ROW(thing,i), ROW_LEN(thing,i) - 1);
            ++i;
        } else {
            thing = removeRow(thing, i);
        }
    }
    return thing;
}

int** rmr(int** thing) /* remove n-th row */
{
    int r;
    scanf(" %d", &r);
    return removeRow(thing, r);
}

int** rmc(int** thing) /* remove n-th column */
{
    int c;
    scanf(" %d", &c);
    return removeBlock(thing, 0, LEN(thing), c, 1);
}

int** isb(int** thing) /* insert block */
{
    int r;
    int c;
    int h;
    int w;
    scanf(" %d %d %d %d", &r, &c, &h, &w);
    int** block = initialize();
    int i;
    for (i = 0; i < h; ++i) {
        block = insertRow(block, readRow(w), LEN(block), 1);
    }
    return insertBlock(thing, block, r, c);
}

int** rmb(int** thing) /* remove block */
{
    int r;
    int h;
    int c;
    int w;
    scanf(" %d %d %d %d", &r, &h, &c, &w);
    return removeBlock(thing, r, h, c, w);
}

int** prt(int** thing) /* print */
{
    int i, j, m;
    int n = LEN(thing);
    for (i = 0; i < n; ++i) {
        m = ROW_LEN(thing,i);
        for (j = 0; j < m; ++j) {
            printf("%d ", ELEM(thing,i,j));
        }
        puts("");
    }
    return thing;
}

int** end(int** thing) /* end */
{
    int i;
    for (i = LEN(thing)-1; i >= -1; --i) {
        free(ROW(thing,i));
    }
    free(thing);
    return NULL;
}

/* vim: set fen: */
