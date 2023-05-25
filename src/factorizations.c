#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include "../include/factorizations.h"

#include <string.h>

MatrixList *crout(MatrixList *list, Matrix *matrice,char *nume_matrice) {
    // matricea trebuie sa fie patratica pentru a face factorizare Crout
    if(matrice -> rows != matrice -> cols) {
        return NULL;
    }
    Matrix *aux = isMatInList(list, nume_matrice);

    if (aux == NULL) {
        printf("Matrix %s doesn't exist!\n", nume_matrice);
        return NULL;
    }

    char nameBuff[256];
    int retResult;
    // citim numele primei matrici L
    do {
        printf("Enter a name for the result matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, nume_matrice)) {
            printf("Matrix name can't be the same as input matrices!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);
    // alocam memorie pentru matricea L
    Matrix *Matrix_L = allocMatrix(matrice -> rows, matrice -> cols, nameBuff);
    // citimi numele pentru matricea U
    do {
        printf("Enter a name for the result matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, nume_matrice)) {
            printf("Matrix name can't be the same as input matrices!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);
    // alocam memoria pentru matricea U
    Matrix *Matrix_U = allocMatrix(matrice->rows, matrice->cols, nameBuff);

    int i, j, p, k;
    // initializam matricea L cu 0
    for(i = 0; i < matrice -> rows; i++) {
        for(j = 0; j < matrice -> rows; j++) {
            Matrix_L -> elems[i][j] = 0;
            Matrix_U -> elems[j][i] = 0;
        }
    }

    // punem 1 pe diagonala principala in matricea U
    for(i = 0; i < matrice -> rows; i++) {
        Matrix_U -> elems[i][i] = 1;
    }
    // factorizarea propiu-zisa
    for(p = 0; p < matrice -> rows; p++) {
        for(i = p; i < matrice -> rows; i++) {
            int suma = 0;
            for(k = 0; k < p; k++) {
                suma += Matrix_L -> elems[i][k] * Matrix_U -> elems[k][p];
            }
            Matrix_L -> elems[i][p] = matrice -> elems[i][p] - suma;
        }
        for(j = p; j < matrice -> rows; j++) {
            int suma = 0;
            for(k = 0; k < p; k++) {
                suma = suma + Matrix_L -> elems[p][k] * Matrix_U -> elems[k][j];
            }
            Matrix_U -> elems[p][j] = (matrice -> elems[p][j] - suma) / Matrix_L -> elems[p][p];
        }
    }
    // printam matricea L
    for(i = 0; i < matrice -> rows; i++) {
        for(j = 0; j < matrice -> cols; j++) {
            printf("%lf ", Matrix_L -> elems[i][j]);
        }
        printf("\n");
    }
    // printam matricea U
    for(i = 0; i < matrice -> rows; i++) {
        for(j = 0; j < matrice -> cols; j++) {
            printf("%lf ", Matrix_U -> elems[i][j]);
        }
        printf("\n");
    }
    insertMatrix(list, Matrix_L);
    insertMatrix(list, Matrix_U);
    return 0;
}
int main() {
    MatrixList *list;

    list = (MatrixList *) malloc(sizeof(MatrixList));
    list -> nrMats = 0;
    list -> head = NULL;
    readMatrix(list);
    crout(list, list -> head -> mat, "ade");
    freeMatList(list, freeMatrix);
    return 0;
}
