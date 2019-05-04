#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "matrix.h"
#include <iostream>

TEST_CASE("matrix is created in constructor№1", "[matrix]")
{
    matrix matr;

    REQUIRE(matr.mat != NULL);
    REQUIRE(matr.rows == 1);
    REQUIRE(matr.cols == 1);
}
