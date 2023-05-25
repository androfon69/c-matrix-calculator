#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include <string.h>
#include <limits.h>

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
// functie pentru a face transpusa unei matrici
Matrix *transposed(Matrix *mat) {
    int i, j;
    // alocam memoria pentru matricea transpusa
    Matrix *new_matrix;
    new_matrix = allocMatrix(mat -> cols, mat -> rows, "Transpusa");
    // transpunerea propiu-zisa
    for(i = 0; i < new_matrix -> rows; i++) {
        for(j = 0; j < new_matrix -> cols; j++) {
            new_matrix -> elems[i][j] = mat -> elems[j][i];
        }
    }
    // returnam matricea transpusa
    return new_matrix;

}

// functia pentru a calcula determinantul unei matrici( daca matricea este
// patratica),
// to be continued
double determinant(Matrix *matrice) {
    if(matrice -> rows != matrice -> cols) {
        printf("Determinantul nu poate fi calculat, matricea nu este patratica\n");
        // returnam INT_MAX, determinantul nu a fost fi putut calculat
        return INT_MAX;
    } else {

    }
}
int main() {
    int i,j;
    Matrix *rezultat1, *rezultat2;
    MatrixList *List;
    List = (MatrixList *) malloc(sizeof(MatrixList));
    List -> nrMats = 0;
    List -> head = NULL;
    readMatrix(List);
    readMatrix(List);
    rezultat1 = transposed(List -> head -> mat);
    rezultat2 = transposed(List -> head -> next -> mat);
    // prima matrice transpusa
    for(i = 0; i < rezultat1 -> rows; i++){
        for(j = 0; j < rezultat1 -> cols; j++) {
            printf("%lf ", rezultat1 -> elems[i][j]);
        }
        printf("\n");
    }
    // a doua matrice transpusa
    for(i = 0; i < rezultat2 -> rows; i++) {
        for(j = 0; j < rezultat2 -> cols; j++) {
            printf("%lf ", rezultat2 -> elems[i][j]);
        }
        printf("\n");
    }
    freeMatList(List, freeMatrix);
    freeMatrix(rezultat1);
    freeMatrix(rezultat2);
}