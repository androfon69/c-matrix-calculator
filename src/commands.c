#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/matrix.h"
#include "../include/operations.h"
#include "../include/commands.h"

const int nrCommands = NR_COMMS;
const char prompt[] = "\033[0;31mmatrix-calc\033[0m $$ ";

const char commands[][COMM_SIZE] =
        {
                "help", "clear", "print", "print-all",
                "read", "delete", "exit", "mult",
                "trans", "det"
        };

const char commandDescriptions[][DESC_SIZE] =
        {
                " -- prints all available commands\n",
                " -- clears the terminal\n",
                " -- prints the input matrix, if it exists\n",
                " -- prints the names of all read matrices\n",
                " -- reads a new matrix from console\n",
                " -- deletes input matrix form the list\n",
                " -- exits the program and deallocates memory\n",
                " -- multiplies input matrices\n",
                " -- transposes input matrix\n",
                " -- prints determinant of input matrix\n"
        };


int isCommandValid(char *command) {

    for (int i = 0; i < nrCommands; ++i) {
        if (!strcmp(commands[i], command)) {
            return i;
        }
    }

    return -1;
}

void help() {
    for (int i = 0; i < nrCommands; ++i) {
        printf("%s", commands[i]);
        printf("%s%s%s",GREEN, commandDescriptions[i], END_COLOUR);
    }
}

void initScreen() {
    printf("%sALL commands should be run as %s%s<command_name> <ENTER KEY>%s\n\n",
           RED, END_COLOUR, GREEN, END_COLOUR);

    printf("%sALL inputs between %s%s<command_name>%s%s and %s%s<ENTER_KEY%s%s will be %s%sIGNORED%s\n\n",
           RED, END_COLOUR, GREEN, END_COLOUR, RED, END_COLOUR, GREEN,
           END_COLOUR, RED, END_COLOUR, GREEN, END_COLOUR);

    printf("%sRun command %s%shelp%s%s to see full command list%s\n\n",
           RED, END_COLOUR, GREEN, END_COLOUR, RED, END_COLOUR);

    printf("--------------------------------------------------------\n\n");

    printf("%sPress %s%s<ENTER KEY>%s%s to continue%s\n\n",
           RED, END_COLOUR, GREEN, END_COLOUR, RED, END_COLOUR);

    getchar();

    clearConsole();
}

void run() {
    MatrixList *list = initMatList();
    char commandBuff[256], inputBuff1[256], inputBuff2[256];
    int noExit = 1;

    while (noExit) {
        printf("%s", prompt);
        scanf("%s", commandBuff);
        clearInput();

        int commandIndex = isCommandValid(commandBuff);

        if (commandIndex == -1) {
            printf("Invalid command! Type help to see list of available commands\n");
        }
        else {
            switch (commandIndex) {
                case HELP:

                    help();
                    break;

                case CLEAR:

                    clearConsole();
                    break;

                case PRINT:

                    printf("Enter the matrix you want to print:\n");
                    scanf("%s", inputBuff1);
                    clearInput();
                    printMatrix(list, inputBuff1);
                    break;

                case PRINT_ALL:

                    printMatrixList(list);
                    break;

                case READ:

                    readMatrix(list);
                    break;

                case DELETE:

                    printf("Enter the matrix you want to delete:\n");
                    scanf("%s", inputBuff1);
                    clearInput();
                    Matrix *mat = isMatInList(list, inputBuff1);
                    if (mat == NULL) {
                        printf("Matrix doesn't exist!\n");
                    }
                    else {
                        deleteMatrix(list, mat, freeMatrix);
                    }

                    break;

                case EXIT:

                    noExit = 0;
                    break;

                case MULT:

                    printf("First matrix: ");
                    scanf("%s", inputBuff1);
                    printf("Second matrix: ");
                    scanf("%s", inputBuff2);
                    multiplication(list, inputBuff1, inputBuff2);

                    break;

                case TRANS:

                    printf("Matrix to transpose: ");
                    scanf("%s", inputBuff1);
                    transpose(list, inputBuff1);

                    break;

                case DET:

                    printf("Matrix: ");
                    scanf("%s", inputBuff1);
                    printf("%lf\n", det(list, inputBuff1));

                    break;

                default:
            }
        }
    }
    freeMatList(list, freeMatrix);
}
