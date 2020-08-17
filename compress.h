#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"

uint64_t countCodes(char *, codeWord **);
codeWord ** sortCodes(codeWord **);
int compareCodeCount(const void *, const void *);
void printCodes(codeWord **);

#endif