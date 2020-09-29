#ifndef TREE_GUARD
#define TREE_GUARD


#include "codeWord.h"

typedef struct codeNode {
    struct codeNode * zero;
    struct codeNode * one;
    codeWord * code;
    uint64_t subcount;
} codeNode;

typedef struct codeTree {
    struct codeNode * root;
    struct codeNode ** node_array;
    struct codeNode * node_memory;
    struct codeWord * word_memory;
} codeTree;

//codeTree* insert();

#endif
