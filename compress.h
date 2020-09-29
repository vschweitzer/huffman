#ifndef COMPRESS_GUARD
#define COMPRESS_GUARD

#include "codeWord.h"
#include "tree.h"

uint64_t count_codes(char *, codeWord **);
codeNode ** sort_nodes(codeNode **);
int compare_node_count(const void *, const void *);
void print_codes(codeWord **);

uint64_t count_nodes(char *, codeNode ***);
void print_nodes(codeNode **);
void print_code_word(codeWord);

#endif
