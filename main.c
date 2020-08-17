#include "util.h"
#include "error.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        return INVALID_ARGUMENT;
    }

    compress(argv[1], argv[2]);

    return SUCCESS;
}