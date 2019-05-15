#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "matrix.h"
#include <iostream>

TEST_CASE("Random number from M - 0.5 to N - 0.5", "[randM]")
{
    double M = 0.1;
    double N = 0.99;
    REQUIRE(randM(M, N) > (0.1 - 0.5));
    REQUIRE(randM(M, N) < (0.99 - 0.5));

    M = 10.0;
    N = 12.0;
    REQUIRE(randM(M, N) > (10 - 0.5));
    REQUIRE(randM(M, N) < (12 - 0.5));
}

TEST_CASE("matrix is created in constructor№1", "[matrix]")
{
    matrix matr;

    REQUIRE(matr.mat != NULL);
    REQUIRE(matr.rows == 1);
    REQUIRE(matr.cols == 1);
}

TEST_CASE("matrix is created in constructor№2", "[matrix]")
{
    int rows = 784;
    int cols = 10;
    matrix matr1(rows, cols);

    REQUIRE(matr1.mat != NULL);
    REQUIRE(matr1.rows == rows);
    REQUIRE(matr1.cols == cols);

    rows = 10;
    cols = 784;
    matrix matr2(rows, cols, 1);

    REQUIRE(matr2.mat != NULL);
    REQUIRE(matr2.rows == rows);
    REQUIRE(matr2.cols == cols);
    REQUIRE(matr2.mat[2][235] != 0);
}

TEST_CASE("matrix override using func init", "[init]")
{
    int rows = 784;
    int cols = 10;
    matrix matr;
    matr.init(rows, cols);

    REQUIRE(matr.mat != NULL);
    REQUIRE(matr.rows == rows);
    REQUIRE(matr.cols == cols);

    rows = 12;
    cols = 236;
    matr.init(rows, cols, 1);

    REQUIRE(matr.mat != NULL);
    REQUIRE(matr.rows == rows);
    REQUIRE(matr.cols == cols);
}

TEST_CASE("matrix transposition", "[transpose]")
{
    int rows = 5;
    int cols = 2;
    matrix matr(rows, cols, 1);
    matrix matrT;

    matrT = matr.transpose();

    REQUIRE(matrT.mat != NULL);
    REQUIRE(matrT.rows == matr.cols);
    REQUIRE(matrT.cols == matr.rows);
}

TEST_CASE("matrix multiplication", "[matrix_multiplication]")
{
    // Given
    matrix A(3, 2);
    matrix B(2, 4);
    matrix C_result;

    float count = 0;
    for (int j = 0; j < 3; j++) {     //
        count++;                      //     | 1, 2 |
        for (int i = 0; i < 2; i++) { // A = | 4, 5 |
            A.mat[j][i] = count;      //     | 7, 8 |
            count++;                  //
        }
    }

    count = 10;                       //
    for (int j = 0; j < 2; j++) {     // B = | 9, 8, 7, 6 |
        count--;                      //     | 4, 3, 2, 1 |
        for (int i = 0; i < 4; i++) { //
            B.mat[j][i] = count;
            count--;
        }
    }

    // When
    C_result = matrix_multiplication(A, B);

    // Then
    float C_expected[3][4] = {// C = A x B
                              {17, 14, 11, 8},
                              {56, 47, 38, 29},
                              {95, 80, 65, 50}};

    REQUIRE(C_result.mat != NULL);
    REQUIRE(C_result.rows == 3);
    REQUIRE(C_result.cols == 4);

    int temp = 0;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 12);
}

TEST_CASE("overloading - (matrix - matrix)", "[Operator overloading]")
{
    // Given
    matrix A(2, 2);
    matrix B(2, 2);
    matrix C_result;

    float count = 0;                  //
    for (int j = 0; j < 2; j++) {     // A = | 1, 2 |
        count++;                      //     | 4, 5 |
        for (int i = 0; i < 2; i++) { //
            A.mat[j][i] = count;
            count++;
        }
    }

    count = 10;                       //
    for (int j = 0; j < 2; j++) {     // B = | 9, 8 |
        count--;                      //     | 6, 5 |
        for (int i = 0; i < 2; i++) { //
            B.mat[j][i] = count;
            count--;
        }
    }

    // When
    C_result = A - B;

    // Then
    float C_expected[2][2] = {// C_expected = A - B;
                              {-8, -6},
                              {-2, 0}};

    int temp = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 4);
}

TEST_CASE("overloading * (matrix * matrix) ", "[Operator overloading]")
{
    // Given
    matrix A(2, 2);
    matrix B(2, 2);
    matrix C_result;

    float count = 0;                  //
    for (int j = 0; j < 2; j++) {     // A = | 1, 2 |
        count++;                      //     | 4, 5 |
        for (int i = 0; i < 2; i++) { //
            A.mat[j][i] = count;
            count++;
        }
    }

    count = 10;                       //
    for (int j = 0; j < 2; j++) {     // B = | 9, 8 |
        count--;                      //     | 6, 5 |
        for (int i = 0; i < 2; i++) { //
            B.mat[j][i] = count;
            count--;
        }
    }

    // When
    C_result = A * B;

    // Then
    float C_expected[2][2] = {// C_expected = A * B;
                              {9, 16},
                              {24, 25}};

    int temp = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 4);
}

TEST_CASE("overloading + (matrix + matrix)", "[Operator overloading]")
{
    // Given
    matrix A(2, 2);
    matrix B(2, 2);
    matrix C_result;

    float count = 0;                  //
    for (int j = 0; j < 2; j++) {     // A = | 1, 2 |
        count++;                      //     | 4, 5 |
        for (int i = 0; i < 2; i++) { //
            A.mat[j][i] = count;
            count++;
        }
    }

    count = 10;                       //
    for (int j = 0; j < 2; j++) {     // B = | 9, 8 |
        count--;                      //     | 6, 5 |
        for (int i = 0; i < 2; i++) { //
            B.mat[j][i] = count;
            count--;
        }
    }

    // When
    C_result = A + B;

    // Then
    float C_expected[2][2] = {// C_expected = A + B;
                              {10, 10},
                              {10, 10}};

    int temp = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 4);
}

TEST_CASE("overloading - (matrix - number)", "[Operator overloading]")
{
    // Given
    matrix A(2, 2);
    matrix C_result;

    float count = 0;                  //
    for (int j = 0; j < 2; j++) {     // A = | 1, 2 |
        count++;                      //     | 4, 5 |
        for (int i = 0; i < 2; i++) { //
            A.mat[j][i] = count;
            count++;
        }
    }

    // When
    C_result = A - 15;

    // Then
    float C_expected[2][2] = {// C_expected = A - 15;
                              {-14, -13},
                              {-11, -10}};

    int temp = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 4);
}

TEST_CASE("overloading + (matrix + number)", "[Operator overloading]")
{
    // Given
    matrix A(2, 2);
    matrix C_result;

    float count = 0;                  //
    for (int j = 0; j < 2; j++) {     // A = | 1, 2 |
        count++;                      //     | 4, 5 |
        for (int i = 0; i < 2; i++) { //
            A.mat[j][i] = count;
            count++;
        }
    }

    // When
    C_result = A + 13;

    // Then
    float C_expected[2][2] = {// C_expected = A + 13;
                              {14, 15},
                              {17, 18}};

    int temp = 0;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (C_result.mat[i][j] == C_expected[i][j]) {
                temp++;
            }
        }
    }

    REQUIRE(temp == 4);
}
