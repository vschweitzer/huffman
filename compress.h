#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"
#include "tree.h"

uint64_t countCodes(char *, codeWord **);
codeWord ** sortCodes(codeWord **);
int compareCodeCount(const void *, const void *);
void printCodes(codeWord **);
// Assumes codeWord * array is ordered ascending by count
codeTree * makeTree(codeWord **, uint8_t);

#endif