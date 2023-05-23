#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListNode {
    Matrix *mat;
    struct ListNode *next;
} ListNode;

typedef struct MatrixList {
    int nrMats;
    struct ListNode *head;
} MatrixList;

MatrixList* initMatList();
void insertMatrix(MatrixList *list, Matrix *mat);
MatrixList* freeMatList(MatrixList *list);

#endif
