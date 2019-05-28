#include "NeuralNetworks.h"
#include "matrix.h"
#include <iostream>


void launchTrain(NeuralNetwork ner);

int main() {

    return 0;
}

void launchTrain(NeuralNetwork ner)
{
    FILE* file;
    char* mass;
    char* pch;
    char buff[20000];

    matrix inputs(ner.in, 1);
    matrix targets(ner.on, 1);
    int correct_label;

    for (int era = 0; era < ner.er; era++) {
        file = fopen("mnist_train.csv", "r");
        int count = 0;
        while (count < ner.cyc) {
            mass = fgets(buff, 20000, file);
            pch = strtok(mass, ",");

            correct_label = atoi(pch);
            for (int i = 0; i < ner.on; i++) {
                targets.mat[i][0] = 0.01;
            }
            targets.mat[correct_label][0] = 0.99;

            for (int i = 0; i < ner.in; i++) {
                pch = strtok(NULL, ",");
                inputs.mat[i][0] = (atoi(pch) / 255.001 * 0.99) + 0.01;
            }
            ner.train(inputs, targets);
            count++;
        }
        fclose(file);
    }
}
