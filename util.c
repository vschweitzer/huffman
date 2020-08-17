#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "util.h"
#include "error.h"
#include "codeWord.h"
#include "compress.h"

uint8_t compress(char * input_file, char * output_file) {
    codeWord * bytes[256], * word_buffer;
    uint64_t bytes_in = 0;

    if(!input_file || !output_file) {
        return INVALID_ARGUMENT;
    }

    word_buffer = (codeWord *)calloc(256, sizeof(codeWord));
    if(!word_buffer) {
        return NO_MEMORY;
    }

    for(unsigned int i = 0; i != 256; ++i) {
        bytes[i] = &word_buffer[i];
        bytes[i]->byte = (uint8_t)i;
    }

    bytes_in = countCodes(input_file, bytes);
    printf("Read %"PRIu64" bytes\n", bytes_in);

    sortCodes(bytes);
    printCodes(bytes);

    return SUCCESS;
}