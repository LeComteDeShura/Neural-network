#include "matrix.h"
#include <iostream>

using namespace std;

matrix::matrix()
{
    rows = 1;
    cols = 1;
    mat = new float*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new float[cols];
    }
}
