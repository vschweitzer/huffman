#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>

#include "compress.h"

uint64_t countCodes(char * filename, codeWord ** code_array) {
    FILE * input_file;
    int value;
    uint64_t total_count;

    if(!filename || !code_array) {
        return 0;
    }

    input_file = fopen(filename, "rb");
    if(!input_file) {
        return 0;
    }

    while(!feof(input_file)) {
        uint8_t byte;
        
        value = fgetc(input_file);
        if(feof(input_file)) {
            break;
        }

        byte = (uint8_t) value;
        ++(code_array[byte]->count);
    }
    
    total_count = ftell(input_file);
    fclose(input_file);
    return total_count;
}

// This function is overly complicated, because it has to account for 
// differences in counts that do not fit in an int
int compareCodeCount(const void * a, const void * b) {
    if((*(codeWord **)a)->count >= (*(codeWord **)b)->count) {
        return -1;
    } else {
        return 1;
    }
}

codeWord ** sortCodes(codeWord ** code_array) {
    qsort((void *)(code_array), 256, sizeof(codeWord *), compareCodeCount);
    return code_array;
}

void printCodes(codeWord ** code_array) {
    uint64_t total_bytes = 0;

    for(unsigned int i = 0; i < 256; ++i) {
        if(code_array[i]->count) {
            printf("Byte:  %#04x\nChar:  %c\nCount: %"PRIu64"\n", 
                code_array[i]->byte, 
                isprint(code_array[i]->byte) ? code_array[i]->byte : ' ',
                code_array[i]->count
                );
            total_bytes += code_array[i]->count;
        }
    }
    printf("Total: %"PRIu64"\n", total_bytes);
}
