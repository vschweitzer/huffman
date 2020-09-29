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
    if((*(codeNode **)a)->code->count >= (*(codeNode **)b)->code->count) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * Sort nodes by probability, order is determined by compare_code_count()
 */

codeNode ** sort_nodes(codeNode ** code_array) {
    qsort((void *)(code_array), 256, sizeof(codeNode *), compare_node_count);
    return code_array;
}

/*
// TBD
codeTree ** alloc_node_array();
void disalloc_node_array();
*/

uint64_t count_nodes(char * filename, codeNode *** node_array) {
    codeNode * tree_buffer = NULL;
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
    *node_array = (codeNode **)calloc(256, sizeof(codeNode *));
    // node array
    tree_buffer = (codeNode *)calloc(256, sizeof(codeNode));
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
void print_nodes(codeNode ** node_array) {
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
codeNode * make_tree(codeNode ** node_array) {
    uint8_t len_minus_one = 255;
    codeNode * min_node = NULL, * s_min_node = NULL;

    sort_nodes(node_array);
    while(len_minus_one) {
        codeNode * new_node;

        new_node = calloc(1, sizeof(codeNode));
        if(!new_node) {
            goto fail;
        }

        get_min_two(node_array, &min_node, &s_min_node, len_minus_one);

        --len_minus_one;
    }

    // Get start of values > 0
    // Build tree, write node codes as tree is built

    return *node_array;

    fail:
    return NULL;
}

unsigned int get_min_two(codeNode ** node_array, codeNode ** min_node, codeNode ** s_min_node, uint8_t len_minus_one) {
    if(node_array == NULL) {
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
