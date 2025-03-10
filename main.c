#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "jit.h"
#include <stdio.h>
#include "bf.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    long size = 0;
    long code_size = 0;
    enum tokens *tokens = get_tokens(filename, &size, &code_size);

    if (tokens == NULL) {
        fprintf(stderr, "Failed to read file %s\n", filename);
        return 1;
    }

    u_int8_t *code = generate_code(tokens, size, code_size);
    const int result = run(code, code_size);

    free(tokens);
    free(code);

    return result;
}
