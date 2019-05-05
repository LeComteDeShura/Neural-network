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
