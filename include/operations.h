#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

#define TOL 0.000001

Matrix *multiplication(MatrixList *list, char *matName1, char *matName2);
Matrix *transpose(MatrixList *list, char *matName);
double det(MatrixList *list, char *matNam, int *matExists);

#endif