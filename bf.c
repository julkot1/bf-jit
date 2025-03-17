#include "bf.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


long get_size(const char* filename)
{
  struct stat st;
  if (stat(filename, &st) != 0) {
    perror("Error getting file size");
    return -1;
  }
  return st.st_size;
}
enum tokens get_token(int token)
{
  switch (token) {
    case INC_TOKEN: return bf_inc;
    case DEC_TOKEN: return bf_dec;
    case INC_PTR_TOKEN: return bf_inc_ptr;
    case DEC_PTR_TOKEN: return bf_dec_ptr;
    case PRINT_TOKEN: return bf_print;
    case JMP_OPEN_TOKEN: return bf_jmp_open;
    case JMP_CLOSE_TOKEN: return bf_jmp_close;
    case INPUT_TOKEN: return bf_input;
  }
  return bf_unknown;
}

int get_token_size(int token)
{
  switch (token) {
    case INC_TOKEN: return INC_VAL_SIZE;
    case DEC_TOKEN: return DEC_VAL_SIZE;
    case INC_PTR_TOKEN: return INC_PTR_SIZE;
    case DEC_PTR_TOKEN: return DEC_PTR_SIZE;
    case PRINT_TOKEN: return PRINT_SIZE;
    case JMP_OPEN_TOKEN: return JMP_SIZE;
    case JMP_CLOSE_TOKEN: return JMP_COND_SIZE;
    case INPUT_TOKEN: return INPUT_SIZE;
  }
  return 0;
}
enum tokens *get_tokens(const char * filename, long *size, long *code_size)
{
  FILE *file = fopen(filename, "r");
  *code_size = 1;
  if (!file)
  {
    fprintf(stderr, "Could not open file %s\n", filename);
    return NULL;
  }
  long f_size = get_size(filename);
  enum tokens *tokens = malloc(f_size * sizeof(enum tokens));
  char token;
  int index = 0;
  while( (token = fgetc(file)) != EOF)
  {
     enum tokens token_type = get_token(token);

     if (token_type != bf_unknown)
     {
       tokens[index++] = token_type;
       *code_size += get_token_size(token);
     }

  }
  *size = index;

  return tokens;

}