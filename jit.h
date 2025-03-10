#include <stdint.h>

//inc byte ptr [rdi]
#define INC_VAL_ASM(code, index)\
    code[index++]=0xfe;\
    code[index++]=0x07;
// inc rdi
#define INC_PTR_ASM(code, index)\
    code[index++]=0x48;\
    code[index++]=0xff;\
    code[index++]=0xc7;

//dec byte ptr [rdi]
#define DEC_VAL_ASM(code, index)\
    code[index++]=0xfe;\
    code[index++]=0x0f;
//dec rdi
#define DEC_PTR_ASM(code, index)\
    code[index++]=0x48;\
    code[index++]=0xff;\
    code[index++]=0xcf;


/*
 * push rdi
 * mov rsi, rdi
 * mov rdi, 1
 * mov rax, 1
 * mov rdx, 1
 * syscall
 * pop rdi
 */
#define PRINT_ASM(code, index)\
    code[index++]=0x57;\
    code[index++]=0x48;\
    code[index++]=0x89;\
    code[index++]=0xfe;\
    code[index++]=0xbf;\
    code[index++]=0x01;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0xb8;\
    code[index++]=0x01;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0xba;\
    code[index++]=0x01;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x0f;\
    code[index++]=0x05;\
    code[index++]=0x5f;


/*
 * push rdi
 * mov rsi, rdi
 * mov rdi, 0
 * mov rax, 0
 * mov rdx, 1
 * syscall
 * pop rdi
 */

#define INPUT_ASM(code, index)\
    code[index++]=0x57;\
    code[index++]=0x48;\
    code[index++]=0x89;\
    code[index++]=0xfe;\
    code[index++]=0xbf;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0xb8;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0xba;\
    code[index++]=0x01;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x00;\
    code[index++]=0x0f;\
    code[index++]=0x05;\
    code[index++]=0x5f;

