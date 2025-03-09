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