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
    list->nrMats++;
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->mat = mat;

    newNode->next = list->head;
    list->head = newNode;
}

void deleteMatrix(MatrixList *list, void *mat, void (*freeFunc) (void *)) {
    if (list->head == NULL || !list->nrMats) {
        printf("You haven't read any matrices!\n");
        return;
    }

    if (mat == NULL) {
        printf("Matrix doesn't exist!");
        return;
    }

    ListNode *temp, *prev;

    if (list->head->mat == mat) {
        temp = list->head;
        list->head = list->head->next;
        list->nrMats--;
        freeFunc(temp->mat);
        free(temp);
        return;
    }

    prev = list->head;
    temp = list->head->next;

    while (temp != NULL) {
        if (temp->mat == mat) {
            prev->next = temp->next;
            list->nrMats--;
            freeFunc(temp->mat);
            free(temp);
            return;
        }

        temp = temp->next;
        prev = prev->next;
    }
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
        free(temp);

        temp = head;
    }

    free(list);
    return NULL;
}
