#ifndef MATRIX_H
#define MATRIX_H

double randM(double M, double N);

class matrix {
public:
    int rows;
    int cols;
    float** mat;

    matrix();
    matrix(int r, int c, int total = 0);
    void init(int r, int c, int total = 0);
    matrix transpose();
    matrix operator-(matrix matr);
    void show(int total = 0);
    void free();
    void operator=(matrix matr);
    matrix operator*(matrix matr);
    matrix operator+(matrix matr);
};

matrix matrix_multiplication(matrix Matrix1, matrix Matrix2);

matrix operator-(float ci, matrix matr);

matrix operator-(matrix matr, float ci);

matrix operator+(matrix matr, float ci);

matrix operator+(float ci, matrix matr);

matrix operator*(matrix matr, float ci);

matrix operator*(float ci, matrix matr);

#endif
