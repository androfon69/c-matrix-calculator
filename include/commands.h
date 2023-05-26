#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define NR_COMMS 14
#define COMM_SIZE 32
#define DESC_SIZE 64
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define END_COLOUR "\033[0m"

extern const int nrCommands;
extern const char prompt[];

extern const char commands[][COMM_SIZE];
extern const char commandDescriptions[][DESC_SIZE];

enum commandEnum{
                HELP, CLEAR, PRINT, PRINT_ALL,
                READ, DELETE, EXIT, MULT,
                TRANS, DET, NORM, TRACE,
                INV, LU
                };

int isCommandValid(char *command);
void help();
void initScreen();
void run();

#endif