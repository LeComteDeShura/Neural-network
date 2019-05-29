#include <iostream>
#include "matrix.h"
#include "NeuralNetworks.h"
#include <cmath>
#include <cstring>

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

void NeuralNetwork::train(matrix inputs, matrix targets)
{
    hidden_inputs = matrix_multiplication(wih, inputs);
    hidden_outputs = sigmoida(hidden_inputs);

    final_inputs = matrix_multiplication(who, hidden_outputs);
    final_outputs = sigmoida(final_inputs);

    output_errors = targets - final_outputs;
    whoT = who.transpose();
    hidden_errors = matrix_multiplication(whoT, output_errors);


    a = hidden_outputs.transpose();
    b = 1.0 - final_outputs;
    c = output_errors * final_outputs;
    d = b * c;
    e = matrix_multiplication(d, a);
    f = e * 0.3;
    for (int i = 0; i < on; i++) {
        for (int j = 0; j < hn; j++) {
            who.mat[i][j] = who.mat[i][j] + f.mat[i][j];
        }
    }


    g = inputs.transpose();
    h = 1.0 - hidden_outputs;
    p = hidden_errors * hidden_outputs;
    l = h * p;
    k = matrix_multiplication(l, g);
    m = k * 0.3;
    for (int i = 0; i < hn; i++) {
        for (int j = 0; j < in; j++) {
            wih.mat[i][j] = wih.mat[i][j] + m.mat[i][j];
        }
    }

    if (count == (cyc-1) * er) {
        FILE* file;
        file = fopen("csvfiles//w.csv", "w");
        for (int i = 0; i < hn; i++) {
            for (int j = 0; j < in; j++) {
                fprintf(file, "%f,", wih.mat[i][j]);
            }
        }
        fprintf(file, "\n");

        for (int i = 0; i < on; i++) {
            for (int j = 0; j < hn; j++) {
                fprintf(file, "%f,", who.mat[i][j]);
            }
        }
        fclose(file);
    }
    count++;

    freeAll();
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

matrix NeuralNetwork::recognition(matrix inputs)
{
    hidden_inputs = matrix_multiplication(wih, inputs);
    hidden_outputs = sigmoida(hidden_inputs);

    final_inputs = matrix_multiplication(who, hidden_outputs);
    final_outputs = sigmoida(final_inputs);

    hidden_inputs.free();
    hidden_outputs.free();
    final_inputs.free();

    return final_outputs;
}

void NeuralNetwork::freeAll()
{
    hidden_inputs.free();
    hidden_outputs.free();
    final_inputs.free();
    final_outputs.free();
    hidden_errors.free();
    output_errors.free();
    a.free();
    b.free();
    c.free();
    d.free();
    e.free();
    f.free();

    g.free();
    h.free();
    p.free();
    l.free();
    k.free();
    m.free();

    whoT.free();
}
