#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>

#include "compress.h"

/*
 * This function is overly complicated, because it has to account for
 * differences in counts that do not fit in an int.
 * Sorts ascending
 */
int compare_node_count(const void * a, const void * b) {
    if((*(codeTree **)a)->code->count >= (*(codeTree **)b)->code->count) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * Sort nodes by probability, order is determined by compare_code_count()
 */

codeTree ** sort_nodes(codeTree ** code_array) {
    qsort((void *)(code_array), 256, sizeof(codeTree *), compare_node_count);
    return code_array;
}

/*
// TBD
codeTree ** alloc_node_array();
void disalloc_node_array();
*/

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

/*
 * Print a fixed size array of nodes
 */
void print_nodes(codeTree ** node_array) {
    for(unsigned int i = 0; i < 256; ++i) {
        print_code_word(*(node_array[i]->code));
    }

    return;
}

/*
 * Print a single code word, omitting the code (TODO)
 */
void print_code_word(codeWord c) {
    printf("%#04x : %c : %8"PRIu64" : \n", c.byte, isprint(c.byte) ? c.byte : ' ', c.count);
    return;
}

/*
 * Build binary tree for huffman coding.
 * Assign codes while building.
 */
codeTree * make_tree(codeTree ** node_array) {
    sort_nodes(node_array);

    // Get start of values > 0
    // Build tree, write node codes as tree is built

    return *node_array;
}

unsigned int get_min_two(codeTree ** node_array, codeTree ** min_node, codeTree ** s_min_node, uint8_t len_minus_one) {
    if(!node_array == NULL) {
        return 0;
    }

    if(len_minus_one) {
        if(node_array[0]->subcount < node_array[1]->subcount) {
            min_node = &node_array[0];
            s_min_node = &node_array[1];
        } else {
            min_node = &node_array[1];
            s_min_node = &node_array[0];
        }
    } else {
        s_min_node = NULL;
        min_node = node_array;
        return 1;
    }

    for(unsigned int i = 2; i <= len_minus_one; ++i) {
        if(min_node->subcount > node_array[i]->subcount) {
            s_min_node = min_node;
            min_node = &node_array[i];
        }
    }

    return 2;
}
