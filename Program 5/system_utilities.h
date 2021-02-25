#ifndef SYSTEM_UTILITIES_H
#define SYSTEM_UTILITIES_H
int parseCommandLine(char x[MAX_TOKENS_ON_A_LINE], char *y[MAX_CMD_LINE_LENGTH]); //parse line function
void fillCommandList(void);
int getCommandNumber(char *s);
#endif