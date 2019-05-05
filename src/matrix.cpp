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

matrix::matrix(int r, int c, int total)
{
    rows = r;
    cols = c;
    mat = new float*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float[cols];
    }

    if (total == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = 0;
            }
        }
    }

    if (total == 1) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mat[i][j] = randM(0.1, 0.99);
    }
}

void matrix::init(int r, int c, int total)
{
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
    rows = r;
    cols = c;
    mat = new float*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float[cols];
    }

    if (total == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = 0;
            }
        }
    }

    if (total == 1) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mat[i][j] = randM(0.1, 0.99);
    }
}

matrix matrix::transpose()
{
    matrix Matrixp(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Matrixp.mat[j][i] = mat[i][j];
        }
    }
    return Matrixp;
}

matrix matrix_multiplication(matrix Matrix1, matrix Matrix2)
{
    matrix Matrixp(Matrix1.rows, Matrix2.cols);

    float temp = 0.0;
    for (int i = 0; i < Matrix1.rows; i++) {
        for (int j = 0; j < Matrix2.cols; j++) {
            for (int k = 0; k < Matrix1.cols; k++) {
                temp += Matrix1.mat[i][k] * Matrix2.mat[k][j];
            }
            Matrixp.mat[i][j] = temp;
            temp = 0.0;
        }
    }

    return Matrixp;
}

void matrix::free()
{
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

matrix matrix::operator-(matrix matr)
{
    matrix Matrixp(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrixp.mat[i][j] = mat[i][j] - matr.mat[i][j];
        }
    }
    return Matrixp;
}
