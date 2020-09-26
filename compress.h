#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"
#include "tree.h"

uint64_t count_codes(char *, codeWord **);
codeWord ** sort_codes(codeWord **);
int compare_code_count(const void *, const void *);
void print_codes(codeWord **);
// Assumes codeWord * array is ordered ascending by count
codeTree * make_tree(codeWord **, uint8_t);

#endif
