#include <stdatomic.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include "jit.h"
#include <stdio.h>




// Function pointer type for JIT-generated function
typedef void (*jit_func)(char *);

#define SIZE 512

int main()
{
    
    u_int8_t *code = (u_int8_t *)calloc(512, sizeof(u_int8_t));
    int index =0;

    INC_VAL_ASM(code, index);
    INC_VAL_ASM(code, index);

    INC_PTR_ASM(code, index);

    INC_VAL_ASM(code, index);
    INC_VAL_ASM(code, index);

    DEC_PTR_ASM(code, index);
    DEC_VAL_ASM(code, index);

    //ret
    code[index++]=0xc3;


    void *mem = mmap(NULL, SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    memcpy(mem, code, SIZE);
    char c[]={0,0,0,0,0,0,0,0};
    char *ptr = c;
    for (int i = 0; i < 5; i++) {
        printf("%d\n", c[i]);
    }
    printf("----\n");
    jit_func func = (jit_func)mem;

    func(ptr);

    for (int i = 0; i < 5; i++) {
        printf("%d\n", c[i]);
    }
    munmap(mem, sizeof(code));

    return 0;
}
