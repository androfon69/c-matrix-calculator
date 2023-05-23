#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/list.h"

MatrixList* initMatList() {
    MatrixList *newList = malloc(sizeof(MatrixList));
    newList->nrMats = 0;
    newList->head = NULL;

    return newList;
}

void insertMatrix(MatrixList *list, Matrix *mat) {
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->mat = mat;

    newNode->next = list->head;
    list->head = newNode;
}

MatrixList* freeMatList(MatrixList *list) {
    if (list == NULL) {
        return list;
    }

    ListNode *temp = list->head;
    ListNode *head = list->head;

    while (temp != NULL) {
        head = head->next;

        free(temp->mat->name);
        free(temp->mat->elems[0]);
        free(temp->mat->elems);
        free(temp->mat);
        free(temp);

        temp = head;
    }

    free(list);
    return NULL;
}
