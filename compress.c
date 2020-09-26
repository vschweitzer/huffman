#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>

#include "compress.h"

/*
 * Reads in input file and count byte probability.
 *
 * @param filename the path to the input file.
 * @param code_array address to write the word count array to.
 * @return the total count of bytes read.
 */
uint64_t count_codes(char * filename, codeWord ** code_array) {
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

/*
 * This function is overly complicated, because it has to account for
 * differences in counts that do not fit in an int
 */
int compare_code_count(const void * a, const void * b) {
    if((*(codeWord **)a)->count >= (*(codeWord **)b)->count) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * Sort code by probability, order is determined by compare_code_count()
 */

codeWord ** sort_codes(codeWord ** code_array) {
    qsort((void *)(code_array), 256, sizeof(codeWord *), compare_code_count);
    return code_array;
}

void print_codes(codeWord ** code_array) {
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

uint64_t count_nodes(char * filename, codeTree *** node_array) {
    codeTree * tree_buffer = NULL;
    codeWord * word_buffer = NULL;
    uint64_t byte_count;
    FILE * input_file;

    if(!filename || !node_array) {
        return 0;
    }

    input_file = fopen(filename, "rb");
    if(!input_file) {
        return 0;
    }

    // pointer array
    *node_array = (codeTree **)calloc(256, sizeof(codeTree *));
    // node array
    tree_buffer = (codeTree *)calloc(256, sizeof(codeTree));
    // code array
    word_buffer = (codeWord *)calloc(256, sizeof(codeWord));

    if(!*node_array || !tree_buffer || !word_buffer) {
        goto fail;
    }

    for(unsigned int i = 0; i < 256; ++i) {
        (*node_array)[i] = &tree_buffer[i];
        (*node_array)[i]->code = &word_buffer[i];
        (*node_array)[i]->code->byte = (uint8_t)i;
    }

    while(!feof(input_file)) {
        uint8_t byte;
        byte = (uint8_t)fgetc(input_file);
        // Necessary?
        if(feof(input_file)) {
            break;
        }

        ++((*node_array)[byte]->code->count);
    }

    for(unsigned int i = 0; i < 256; ++i) {
        (*node_array)[i]->subcount = (*node_array)[i]->code->count;
    }

    byte_count = ftell(input_file);
    fclose(input_file);
    return byte_count;

    fail:
    fclose(input_file);

    if(*node_array) {
        free(*node_array);
    }

    if(tree_buffer) {
        free(tree_buffer);
    }

    if(word_buffer) {
        free(word_buffer);
    }
    return 0;
}

void print_nodes(codeTree ** node_array) {
    for(unsigned int i = 0; i < 256; ++i) {
        print_code_word(*(node_array[i]->code));
    }

    return;
}

void print_code_word(codeWord c) {
    printf("%#04x : %c : %8"PRIu64" : \n", c.byte, isprint(c.byte) ? c.byte : ' ', c.count);
    return;
}
