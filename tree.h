#ifndef TREE_GUARD
#define TREE_GUARD


#include "codeWord.h"

typedef struct codeTree {
    codeTree* left;
    codeTree* right;
    codeWord *code;
    uint64_t subcount;
} codeTree;



//codeTree* insert();

#endif