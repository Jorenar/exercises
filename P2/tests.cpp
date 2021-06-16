#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>

#include "matrix.hpp"

using namespace std;


void ok(){
    cout  << "OK" << endl;
}

void err(string msg){
    cout << "ERROR: " << msg << endl;
}

void test_random_double(){

    double r_01 = random_double(0, 1);
    if (r_01 >= 0 and r_01 <= 1) ok();
    else err("Liczba spoza przedzialu!");

    double r_01_2 = random_double(0, 1);
    if (r_01 != r_01_2) ok();
    else err("Nielosowe liczby!");

    double r_10_20 = random_double(10, 20);
    if (r_10_20 >= 10 and r_10_20 <= 20) ok();
    else err("Liczba spoza przedzialu!");
}

void test_random_matrix(){

    Matrix* mat = random_matrix(3, 4);

    if (mat->rows == 3) ok();
    else err("Zla liczba wierszy!");

    if (mat->cols == 4) ok();
    else err("Zla liczba kolumn!");

    bool error = false;
    for (int i = 0; i > mat->cols * mat->rows; i++){
        if (mat->values[i] < 0 or mat->values[i] > 10){
            error = true;
        }
    }
    if (!error) ok();
    else err("Liczby spoza przedzialu!");

    delete mat;
}


void test_apply(){

    int cols = 2;
    int rows = 2;
    Matrix* mat = random_matrix(rows, cols);

    int size = rows * cols;
    Matrix copy_mat;
    copy_mat.rows = rows;
    copy_mat.cols = cols;
    copy_mat.values = new double[size];

    for (int i = 0; i < size; i++){
        copy_mat.values[i] = mat->values[i];
    }

    apply(square, mat);

    bool error = false;
    for (int i = 0; i < size; i++){
        if (abs(mat->values[i] - square(copy_mat.values[i])) > 1e-6){
            error = true;
        }
    }

    if (!error) ok();
    else err("Blad w wartosciach apply!");

    delete mat;

}

int main() {

    srand(time(nullptr));
    test_random_double();
    test_random_matrix();
    test_apply();

    return 0;
}
