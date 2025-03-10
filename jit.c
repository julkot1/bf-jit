#include "jit.h"
#include <stdio.h>
u_int8_t *generate_code(enum tokens *tokens, long size, long code_size)
{
  u_int8_t *code = calloc(code_size, sizeof(u_int8_t));
  int index = 0;
  for (long i = 0; i < size; i++)
  {
    switch (tokens[i])
    {
      case bf_inc:
        INC_VAL_ASM(code, index);
      break;
      case bf_dec:
        DEC_VAL_ASM(code, index);
      break;
      case bf_inc_ptr:
        INC_PTR_ASM(code, index);
      break;
      case bf_dec_ptr:
        DEC_PTR_ASM(code, index);
      break;
      case bf_input:
        INPUT_ASM(code, index);
        break;
      case bf_print:
        PRINT_ASM(code, index);
        break;
    }
  }
  code[index]=0xc3;
  return code;
}

int run(u_int8_t *code, long code_size)
{
  void *mem = mmap(NULL, code_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                 MAP_ANON | MAP_PRIVATE, -1, 0);
  if (mem == MAP_FAILED) {
    perror("mmap failed");
    return 1;
  }
  memcpy(mem, code, code_size);

  char c[100] = {0};
  char *ptr = c;

  bf_func func = (bf_func)mem;

  func(ptr);

  munmap(mem, code_size);
  return 0;
}