#ifndef CODE_WORD_GUARD
#define CODE_WORD_GUARD

#include <stdint.h>

typedef struct codeWord {
    // what byte does the codeWord represent
    uint8_t byte;
    uint8_t *code;
    uint16_t code_length;
    // how often is the codeWord used
    uint64_t count;
} codeWord;

#endif