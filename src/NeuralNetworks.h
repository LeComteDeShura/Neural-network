#ifndef NEURALNETWORKS_H
#define NEURALNETWORKS_H
#include "matrix.h"


matrix sigmoida(matrix Matrix);

class NeuralNetwork{
    public:
        int in;
        int on;
        int hn;
        int lr;

        matrix wih;
        matrix who;

        int er;
        int cyc;

        NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, float learningrate, int era, int cycles);
        void back(matrix inputs, matrix targets);
        void freeAll();
        void train(matrix inputs, matrix targets);
        void init_w();
        matrix recognition(matrix inputs);
    private:
        matrix hidden_inputs;
        matrix hidden_outputs;
        matrix final_inputs;
        matrix final_outputs;
        matrix whoT;

        matrix hidden_errors;
        matrix output_errors;



        int count;

        matrix a;
        matrix b;
        matrix c;
        matrix d;
        matrix e;
        matrix f;

        matrix g;
        matrix h;
        matrix p;
        matrix l;
        matrix k;
        matrix m;

};
#endif
