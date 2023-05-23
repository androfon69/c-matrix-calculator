#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct Matrix {
    int rows, cols;
    char *name;
    double **elems;
} Matrix;

Matrix* readMatrix();

#endif