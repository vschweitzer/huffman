#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"
#include "tree.h"

uint64_t count_codes(char *, codeWord **);
codeTree ** sort_nodes(codeTree **);
int compare_node_count(const void *, const void *);
void print_codes(codeWord **);

uint64_t count_nodes(char *, codeTree ***);
void print_nodes(codeTree **);
void print_code_word(codeWord);

#endif
