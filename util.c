#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "util.h"
#include "error.h"
#include "codeWord.h"
#include "compress.h"

uint8_t compress(char * input_file, char * output_file) {
    codeNode ** node_array = NULL;
    uint64_t byte_count;

    if(!input_file || !output_file) {
        return INVALID_ARGUMENT;
    }

    byte_count = count_nodes(input_file, &node_array);
    if(!byte_count) {
        fprintf(stderr, "Could not read any bytes from %s", input_file);
        return ERROR;
    }
    printf("Read %"PRIu64" bytes.\n", byte_count);
    sort_nodes(node_array);
    print_nodes(node_array);

    return SUCCESS;
}
