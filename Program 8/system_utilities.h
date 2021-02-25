#ifndef SYSTEM_UTILITIES_H
#define SYSTEM_UTILITIES_H

#include <iostream>
#include "stdlib.h"
#include "string.h"
#include "machines.h"

int parseCommandLine(char x[MAX_TOKENS_ON_A_LINE], char *y[MAX_CMD_LINE_LENGTH]); //parse line function
void fillCommandList(void);
int getCommandNumber(char *s);
void printError(int err); //error printer function
void systemStatus();
int addNetworkNode(char *toks[], int numberToks);
int deleteNetworkNode(char *toks[], int numberToks);
int str2int(char *string);
int findNode(char *n);
int wait(void);
extern computer *network[MAX_NETWORK_NODES];
#endif
