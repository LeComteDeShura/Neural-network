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
    REQUIRE(count == 4);
}

TEST_CASE("calc_test_recognition", "[recognition]")
{
    NeuralNetwork nn(2, 2, 2, 0.333, 1, 1);

    nn.wih.mat[0][0] = 2;
    nn.wih.mat[1][0] = 2;
    nn.wih.mat[0][1] = 2;
    nn.wih.mat[1][1] = 2;

    nn.who.mat[1][0] = 2;
    nn.who.mat[0][0] = 2;
    nn.who.mat[0][1] = 2;
    nn.who.mat[1][1] = 2;

    matrix input(2, 2);
    input.mat[1][0] = 2;
    input.mat[0][0] = 2;
    input.mat[0][1] = 2;
    input.mat[1][1] = 2;


    matrix exp(2, 2);
    exp.mat[1][0] = 0.9819;
    exp.mat[0][0] = 0.9819;
    exp.mat[0][1] = 0.9819;
    exp.mat[1][1] = 0.9819;


    input = nn.recognition(input);

    input.mat[0][0] = int(input.mat[0][0] * 10000)/10000.0;
    input.mat[1][0] = int(input.mat[1][0] * 10000)/10000.0;
    input.mat[1][1] = int(input.mat[1][1] * 10000)/10000.0;
    input.mat[0][1] = int(input.mat[0][1] * 10000)/10000.0;

    REQUIRE(exp.mat[0][0] == input.mat[1][0]);
    REQUIRE(exp.mat[0][0] == input.mat[0][0]);
    REQUIRE(exp.mat[0][0] == input.mat[1][1]);
    REQUIRE(exp.mat[0][0] == input.mat[0][1]);
}

TEST_CASE("calc_test_train", "[train]")
{
    NeuralNetwork nn(2, 2, 2, 0.333, 2, 2);

    nn.wih.mat[0][0] = 2;
    nn.wih.mat[1][0] = 2;
    nn.wih.mat[0][1] = 2;
    nn.wih.mat[1][1] = 2;

    nn.who.mat[1][0] = 2;
    nn.who.mat[0][0] = 2;
    nn.who.mat[0][1] = 2;
    nn.who.mat[1][1] = 2;

    matrix input(2, 2);
    input.mat[1][0] = 2;
    input.mat[0][0] = 2;
    input.mat[0][1] = 2;
    input.mat[1][1] = 2;

    matrix targets(2, 2);
    targets.mat[1][0] = 0.1;
    targets.mat[0][0] = 0.1;
    targets.mat[0][1] = 0.1;
    targets.mat[1][1] = 0.9;


    matrix exp_wih(2, 2);
    exp_wih.mat[1][0] = 1.99908;
    exp_wih.mat[0][0] = 1.99908;
    exp_wih.mat[0][1] = 1.99908;
    exp_wih.mat[1][1] = 1.99908;
    matrix exp_who(2, 2);
    exp_who.mat[1][0] = 1.99573;
    exp_who.mat[0][0] = 1.9922;
    exp_who.mat[0][1] = 1.9922;
    exp_who.mat[1][1] = 1.99573;

    nn.train(input, targets);

    nn.wih.mat[0][0] = int(nn.wih.mat[0][0] * 100000)/100000.0;
    nn.wih.mat[1][0] = int(nn.wih.mat[1][0] * 100000)/100000.0;
    nn.wih.mat[1][1] = int(nn.wih.mat[1][1] * 100000)/100000.0;
    nn.wih.mat[0][1] = int(nn.wih.mat[0][1] * 100000)/100000.0;

    nn.who.mat[0][0] = int(nn.who.mat[0][0] * 100000)/100000.0;
    nn.who.mat[1][0] = int(nn.who.mat[1][0] * 100000)/100000.0;
    nn.who.mat[1][1] = int(nn.who.mat[1][1] * 100000)/100000.0;
    nn.who.mat[0][1] = int(nn.who.mat[0][1] * 100000)/100000.0;

    REQUIRE(exp_wih.mat[0][0] == nn.wih.mat[0][0]);
    REQUIRE(exp_wih.mat[1][0] == nn.wih.mat[1][0]);
    REQUIRE(exp_wih.mat[0][1] == nn.wih.mat[0][1]);
    REQUIRE(exp_wih.mat[1][1] == nn.wih.mat[1][1]);

    REQUIRE(exp_who.mat[0][0] == nn.who.mat[0][0]);
    REQUIRE(exp_who.mat[1][0] == nn.who.mat[1][0]);
    REQUIRE(exp_who.mat[0][1] == nn.who.mat[0][1]);
    REQUIRE(exp_who.mat[1][1] == nn.who.mat[1][1]);
}
