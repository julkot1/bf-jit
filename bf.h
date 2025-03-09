#ifndef BF
#define BF
#define INC_TOKEN '+'
#define DEC_TOKEN '-'
#define INC_PTR_TOKEN '>'
#define DEC_PTR_TOKEN '<'
#define INPUT_TOKEN '*'
#define OUTPUT_TOKEN '.'
#define JMP_OPEN_TOKEN '['
#define JMP_CLOSE_TOKEN ']'


enum tokens {
    bf_inc, bf_dec, bf_inc_ptr, bf_dec_ptr, bf_input, bf_output, bf_jmp_open, bf_jmp_close
};
#endif