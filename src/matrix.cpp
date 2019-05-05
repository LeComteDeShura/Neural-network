#include "matrix.h"
#include <iostream>

using namespace std;

double randM(double M, double N)
{
    return (M + (rand() / (RAND_MAX / (N - M)))) - 0.5;
}

matrix::matrix()
{
    rows = 1;
    cols = 1;
    mat = new float*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float[cols];
    }
}

matrix::matrix(int r, int c, int total ){


    rows = r;
    cols = c;
    mat = new float *[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float [cols];
    }

    if (total == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = 0;
            }
        }
    }

    if(total == 1){
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mat[i][j] = randM(0.1, 0.99);
    }
}

void matrix::init(int r, int c, int total ){
    for (int i = 0; i < rows; i++) {
        delete []mat[i];
    }
    delete []mat;
    rows = r;
    cols = c;
    mat = new float *[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float [cols];
    }

    if (total == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = 0;
            }
        }
    }


    if(total == 1){
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mat[i][j] = randM(0.1, 0.99);
    }
}
