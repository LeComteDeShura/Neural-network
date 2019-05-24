#include <iostream>
#include "matrix.h"
#include "NeuralNetworks.h"
#include <cmath>

matrix sigmoida(matrix Matrix){
    float e = 2.7180;
    matrix Matrixp(Matrix.rows, Matrix.cols);

    for (int i = 0; i < Matrix.rows; i++) {
        for (int j = 0; j < Matrix.cols; j++) {
             Matrixp.mat[i][j] = 1 / (1 + pow(e, (Matrix.mat[i][j] * -1)));
        }
    }
    return Matrixp;
}

NeuralNetwork::NeuralNetwork( int input_nodes, int hidden_nodes, int output_nodes, float learningrate, int era, int cycles)
{
    in = input_nodes;
    hn = hidden_nodes;
    on = output_nodes;

    er = era;
    cyc = cycles;
    count = 0;
    wih.init(hn, in, 1);
    who.init(on, hn, 1);
}

void NeuralNetwork::init_w()
{
    FILE* file;
    char* mass;
    char* pch;
    char buff[4500000];

    file = fopen("csvfiles//w.csv", "r");

    mass = fgets(buff, 4000000, file);

    for (int i = 0; i < hn; i++) {
        for (int j = 0; j < in; j++) {
            if (i == 0 && j == 0) {
                pch = strtok(mass, ",");
                wih.mat[0][0] = atof(pch);
                continue;
            }
            pch = strtok(NULL, ",");

            wih.mat[i][j] = atof(pch);
        }
    }

    mass = fgets(buff, 50000, file);
    for (int i = 0; i < on; i++) {
        for (int j = 0; j < hn; j++) {
            if (i == 0 && j == 0) {
                pch = strtok(mass, ",");
                who.mat[0][0] = atof(pch);
                continue;
            }
            pch = strtok(NULL, ",");
            who.mat[i][j] = atof(pch);
        }
    }

    fclose(file);
}
