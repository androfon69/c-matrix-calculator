#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include <string.h>

// functie pentru inmultirea a doua matrici
Matrix *multiplication(Matrix *mat1, Matrix *mat2) {
    int i, j, k;
    /* verificam daca putem inmulti celo doua matrici, numarul de coloane ale
     * primei matrici sa fie egal cu numarul de linii ale celei de a doua
     */
    if(mat1 -> cols == mat2 -> rows) {
        // putem face inmultirea
        // alocam memoria pentru noua matrice
        Matrix *new_matrix;
        new_matrix = (Matrix *) malloc(sizeof(Matrix));
        new_matrix -> rows = mat1 -> rows;
        new_matrix -> cols = mat2 -> cols;
        new_matrix -> name = (char *) malloc(9 * sizeof(char));
        strcpy(new_matrix -> name, "Rezultat");
        new_matrix -> elems = (double **) malloc(new_matrix -> rows * sizeof(double *));
        new_matrix->elems[0] = malloc(new_matrix->rows * new_matrix->cols * sizeof(double));
        for (int i = 1; i < new_matrix->rows; ++i) {
            new_matrix->elems[i] = new_matrix->elems[0] + i * new_matrix->cols;
        }
        // initializam matricea cu 0
        for(i = 0; i < new_matrix -> rows; i++) {
            for(j = 0; j < new_matrix -> cols; j++) {
                new_matrix -> elems[i][j] = 0;
            }
        }
        // inmultirea propiu-zisa
        for(i = 0; i < new_matrix -> rows; i++) {
            for(j = 0; j < new_matrix -> cols; j++) {
                for(k = 0; k < mat1 -> cols; k++) {
                    new_matrix -> elems[i][j] +=
                            mat1 -> elems[i][k] * mat2 -> elems[k][j];
                }
            }
        }
        // returnam matricea rezultata in urma inmultirii
        return new_matrix;
    } else {
        // nu putem face inmultirea
        printf("Inmultirea imposibila, dimensiuni incompatibile ale matricilor\n");
        return NULL;
    }
}
int main() {
    int i,j;
    Matrix *matrice1, *matrice2, *rezultat;
    matrice1 = readMatrix();
    matrice2 =  readMatrix();
    rezultat = multiplication(matrice1, matrice2);
    if(rezultat != 0) {
        printf("Matricea rezultata este:\n");
        for(i = 0; i < rezultat -> rows; i++) {
            for(j = 0; j < rezultat -> cols; j++) {
                printf("%lf ", rezultat -> elems[i][j]);
            }
            printf("\n");
        }
        freeMatrix(rezultat);
    }
    freeMatrix(matrice1);
    freeMatrix(matrice2);
}