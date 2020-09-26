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

// 1 marks the larger subcount, 0 the smaller
codeTree * make_tree(codeWord ** code_array, uint8_t length_minus_one) {
    // One codeWord
    if(!length_minus_one) {
        codeTree * root = NULL;
        root = (codeTree *)calloc(1, sizeof(codeTree));
        root->code = code_array[0];
        root->subcount = root->code->count;
        return root;
    } else if(length_minus_one == 1) {
        codeTree * root, * zero, * one;
        root = (codeTree *)calloc(1, sizeof(codeTree));
        zero = (codeTree *)calloc(1, sizeof(codeTree));
        one = (codeTree *)calloc(1, sizeof(codeTree));

        zero->code = code_array[0];
        zero->subcount = zero->code->count;

        one->code = code_array[1];
        one->subcount = one->code->count;

        root->zero = zero;
        root->one = one;
        root->subcount = zero->subcount + one->subcount;

        return root;
    } else {
        // First two codeWords build the first tree
        uint8_t index = 2;
        uint8_t counter_minus_one = length_minus_one;
        codeTree * root;
        // Make first tree out of first two codeWords
        root = make_tree(code_array, 1);

        do {


            printf("Counter: %d\n", counter_minus_one);
        } while (counter_minus_one--);

        return NULL;
    }
}
