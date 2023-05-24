#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

MatrixList* initMatList() {
    MatrixList *newList = malloc(sizeof(MatrixList));
    newList->nrMats = 0;
    newList->head = NULL;

    return newList;
}

void insertMatrix(MatrixList *list, void *mat) {
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->mat = mat;

    newNode->next = list->head;
    list->head = newNode;
}

MatrixList* freeMatList(MatrixList *list, void (*freeFunc) (void *)) {
    if (list == NULL) {
        return list;
    }

    ListNode *temp = list->head;
    ListNode *head = list->head;

    while (temp != NULL) {
        head = head->next;

        freeFunc(temp->mat);
        temp->mat = NULL;

        temp = head;
    }

    free(list);
    return NULL;
}
