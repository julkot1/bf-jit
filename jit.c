#include "jit.h"
#include <stdio.h>

int8_t token_size(int token)
{
  switch (token) {
    case bf_inc: return INC_VAL_SIZE;
    case bf_dec: return DEC_VAL_SIZE;
    case bf_inc_ptr: return INC_PTR_SIZE;
    case bf_dec_ptr: return DEC_PTR_SIZE;
    case bf_print: return PRINT_SIZE;
    case bf_jmp_close: return JMP_SIZE;
    case bf_jmp_open: return JMP_COND_SIZE;
    case bf_input: return INPUT_SIZE;
    default: return 0;
  }
  return 0;
}
int8_t get_matching(int rev, enum tokens * tokens, long i, int index)
{
  int balance = 1;
  int8_t offset = rev == 1 ? 0 : token_size(tokens[i]);
  while (balance)
  {
      if (rev == 1) i++;
      else if (rev == 0) i--;

      offset += token_size(tokens[i]);
      if (rev == 1)
      {
        if (tokens[i] == bf_jmp_open) balance++;
        else if (tokens[i] == bf_jmp_close) balance--;
      }
      if (rev == 0)
      {
        if (tokens[i] == bf_jmp_open) balance--;
        else if (tokens[i] == bf_jmp_close) balance++;
      }
  }
  return offset;
}

u_int8_t *generate_code(enum tokens *tokens, long size, long code_size)
{
  u_int8_t *code = calloc(code_size, sizeof(u_int8_t));
  int index = 0;
  int8_t offset;
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
      case bf_jmp_open:
        offset = get_matching(1, tokens, i, index);
        JUMP_COND_ASM(code, index, offset);
      break;
      case bf_jmp_close:
        offset = get_matching(0, tokens, i, index);
        offset *= -1;
        JUMP_ASM(code, index, offset);
      break;
      default:
        break;;
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