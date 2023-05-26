#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include "../include/factorizations.h"

#include <math.h>
#include <string.h>


void crout(MatrixList *list, char *matName) {
    Matrix *mat = isMatInList(list, matName);


    if (mat == NULL) {
        printf("Matrix %s doesn't exist!\n", matName);
        return;
    }

    if(mat->rows != mat->cols) {
        printf("Can't perform LU decomposition on non-square matrix\n");
        return;
    }

    char nameBuff[256];
    int retResult;

    do {
        printf("Enter a name for the Lower matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrix!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *L = allocMatrix(mat->rows, mat->cols, nameBuff);

    do {
        printf("Enter a name for the Upper matrix:\n");
        scanf("%s", nameBuff);
        clearInput();

        if (!strcmp(nameBuff, matName)) {
            printf("Matrix name can't be the same as input matrix!\n");
            retResult = 0;
        }
        else {
            retResult = isNameValid(list, nameBuff);
        }
    } while (retResult == 0);

    Matrix *U = allocMatrix(mat->rows, mat->cols, nameBuff);

    int i, j, p, k;
    int size = mat->rows;

    /* Initializing L and U matrices with 0 */
    for(i = 0; i < size; ++i) {
        for(j = 0; j < size; ++j) {
            L->elems[i][j] = 0;
            U->elems[j][i] = 0;
        }
    }

    /* Initializing U's diagonal with 1 */
    for(i = 0; i < size; i++) {
        U->elems[i][i] = 1;
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
MatrixList *QR(MatrixList *list, Matrix *matrice, char *nume_matrice) {
    register int  i,  j, k;
    // matricea trebuie sa fie patratica pentru a face factorizare QR
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
    // citim numele primei matrici Q
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
    // alocam memorie pentru matricea Q
    Matrix *Matrix_Q = allocMatrix(matrice -> rows, matrice -> cols, nameBuff);
    // citimi numele pentru matricea R
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
    // alocam memoria pentru matricea R
    Matrix *Matrix_R = allocMatrix(matrice->rows, matrice->cols, nameBuff);
    // initializam matricea L cu 0
    for(i = 0; i < matrice -> rows; i++) {
        for(j = 0; j < matrice -> rows; j++) {
            Matrix_Q -> elems[i][j] = 0;
            Matrix_R -> elems[j][i] = 0;
        }
    }

    // Copierea matricei A în matricea R
    for (i = 0; i < matrice -> rows; i++) {
        for (j = 0; j < matrice -> rows; j++) {
            Matrix_R -> elems[i][j] = matrice -> elems[i][j];
        }
    }

    // Iterare prin coloanele matricei A
    for (k = 0; k < matrice -> rows; k++) {
        // Calculul normei coloanei k a matricei R
        double norm = 0.0;
        for (i = k; i < matrice -> rows; i++) {
            norm += Matrix_R -> elems[i][k] * Matrix_R ->elems[i][k];
        }
        norm = sqrt(norm);

        // Actualizarea elementului diagonal principal al matricei R
        if (norm == 0.0) {
            printf("Factorizare QR imposibila: matricea nu are rang maxim!\n");
            return;
        }
        if (Matrix_R -> elems[k][k] < 0) {
            norm = -norm;
        }
        Matrix_R -> elems[k][k] += norm;

        // Calculul coloanei k a matricei Q
        for (i = k; i < matrice -> rows; i++) {
            Matrix_Q -> elems[i][k] = Matrix_R -> elems[i][k] / norm;
        }

        // Actualizarea matricei R
        for (j = k + 1; j < matrice -> rows; j++) {
            double dot_product = 0.0;
            for (i = k; i < matrice -> rows; i++) {
                dot_product += Matrix_Q -> elems[i][k] * Matrix_R -> elems[i][j];
            }
            for (i = k; i < matrice -> rows; i++) {
                Matrix_R -> elems[i][j] -= 2.0 * Matrix_Q -> elems[i][k] * dot_product;
            }
        }
    }
    return NULL;
}
int main() {
    MatrixList *list;


    /* Factorization algorithm */
    for(p = 0; p < size; p++) {
        for(i = p; i < size; i++) {
            int sum = 0;

            for(k = 0; k < p; k++) {
                sum += L->elems[i][k] * U->elems[k][p];
            }

            L->elems[i][p] = mat->elems[i][p] - sum;
        }

        for(j = p; j < size; j++) {
            int sum = 0;

            for(k = 0; k < p; k++) {
                sum = sum + L->elems[p][k] * U->elems[k][j];
            }

            U->elems[p][j] = (mat->elems[p][j] - sum) / L->elems[p][p];
        }
    }

    insertMatrix(list, L);
    insertMatrix(list, U);

    printMatrix(list, L->name);
    printf("\n");
    printMatrix(list, U->name);
}
