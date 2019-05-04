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
