#define CATCH_CONFIG_MAIN

#include "matrix.h"
#include "NeuralNetworks.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("calc_test", "[sigmoida]")
{
    matrix A(2,2);
    A.mat[0][0] = 0.1;
    A.mat[1][0] = 0.2;
    A.mat[1][1] = 0.5;
    A.mat[0][1] = 0.99;

    matrix B;
    B = sigmoida(A);
    B.mat[0][0] = int(B.mat[0][0] * 10000)/10000.0;
    B.mat[1][0] = int(B.mat[1][0] * 10000)/10000.0;
    B.mat[1][1] = int(B.mat[1][1] * 10000)/10000.0;
    B.mat[0][1] = int(B.mat[0][1] * 10000)/10000.0;

    matrix C(2,2);
    C.mat[0][0] = 0.5249;
    C.mat[1][0] = 0.5498;
    C.mat[1][1] = 0.6224;
    C.mat[0][1] = 0.729;

    int count = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if(C.mat[i][j] == B.mat[i][j]){
                count++;
            }
        }
    }
    std::cout << B.mat[1][0] << '\n' << C.mat[1][0];
    REQUIRE(count == 4);
}
