#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"
#include "tree.h"

uint64_t count_codes(char *, codeWord **);
codeWord ** sort_codes(codeWord **);
int compare_code_count(const void *, const void *);
void print_codes(codeWord **);

uint64_t count_nodes(char *, codeTree ***);
void print_nodes(codeTree **);
void print_code_word(codeWord);

#endif
