#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

#define TOL 0.000001

Matrix *multiplication(MatrixList *list, char *matName1, char *matName2);
Matrix *transpose(MatrixList *list, char *matName);
double det(MatrixList *list, char *matNam, int *matExists);
double norm(MatrixList *list, char *matName, int *matExists);
double trace(MatrixList *list, char *matName, int *matExists);
Matrix *inverse(MatrixList *list, char *matName);

#endif