#include "NeuralNetworks.h"
#include "matrix.h"
#include <iostream>


void launchTrain(NeuralNetwork ner);
void launchRecognition(NeuralNetwork ner);

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

void launchTestEfficiency(NeuralNetwork ner)
{
    FILE* file;
    char* mass;
    char* pch;
    char buff[5000];
    file = fopen("mnist_test.csv", "r");

    matrix inputs(784, 1);
    matrix final_outputs;

    float max;
    int label;
    int correct_label;
    int count_label = 0;

    ner.init_w();

    int count = 0;
    while (count < 10001) {
        mass = fgets(buff, 5000, file);
        pch = strtok(mass, ",");
        correct_label = atoi(pch);

        for (int i = 0; i < ner.in; i++) {
            pch = strtok(NULL, ",");
            inputs.mat[i][0] = (atoi(pch) / 255.001 * 0.99) + 0.01;
        }
        final_outputs = ner.recognition(inputs);

        max = final_outputs.mat[0][0];
        label = 0;
        for (int i = 0; i < ner.on; i++) {
            if (max < final_outputs.mat[i][0]) {
                label = i;
                max = final_outputs.mat[i][0];
            }
        }

        if (label == correct_label) {
            count_label++;
        }

        count++;
    }

    fclose(file);
    std::cout << '\n'
              << "эффективность - " << (count_label / (count + 0.1)) * 100.1
              << '%' << '\n';
}

void launchRecognition(NeuralNetwork ner)
{
    char path[40] = "image//";
    char name[20];
    std::cout << "Enter image name: " << '\n';
    cin >> name;
    strcat(path, name);

    int width = 28, height = 28, bpp = 1;
    uint8_t* image = stbi_load(path, &width, &height, &bpp, 1);

    matrix inputs(ner.in , 1);
    int i = 0;
    while (i < ner.in) {
        inputs.mat[i][0] = float(255 - unsigned(image[i]));
        i++;
    }

    ner.init_w();

    for (int i = 1; i < ner.in; i++) {
        inputs.mat[i][0] = (inputs.mat[i][0] / 255.001 * 0.99) + 0.01;
    }

    matrix final_outputs;
    final_outputs = ner.recognition(inputs);

    float max;
    max = final_outputs.mat[0][0];
    int label = 0;
    for (int i = 0; i < ner.on; i++) {
        if (max < final_outputs.mat[i][0]) {
            label = i;
            max = final_outputs.mat[i][0];
        }
    }

    std::cout << '\n';
    cout << "answer network - " << label << '\n';
}
