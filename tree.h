#ifndef TREE_GUARD
#define TREE_GUARD


#include "codeWord.h"

typedef struct codeTree {
    struct codeTree* zero;
    struct codeTree* one;
    codeWord *code;
    uint64_t subcount;
} codeTree;



//codeTree* insert();

#endif