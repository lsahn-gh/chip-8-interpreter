#ifndef CHIP8_H
#define CHIP8_H

#include "types.h"

#define MEM_SIZE    4096 /* 4KB */
#define SCREEN      64*32 /* Width*Height */
#define STACK_LVL   16 /* Up to 16 lvls */
#define STACK_SIZE  STACK_LVL

#define R0  0       /* Move 0 bits to the right */
#define R4  4       /* Move 4 bits */
#define R8  8       /* Move 8 bits */
#define GET_V(_OPCODE, _MOVE)   ((_OPCODE >> _MOVE) & 0x000F)

typedef enum { /* V0-VF registers */
    V0 = 0,
    V1, V2, V3,
    V4, V5, V6,
    V7, V8, V9,
    VA, VB, VC,
    VD, VE, VF,
    REGISTERS
} Register;

typedef struct _Chip8
{
    ubyte       gfx[SCREEN];
    ubyte       memory[MEM_SIZE];
    ubyte       V[REGISTERS];

    ushort      opcode;
    ushort      pc;
    ushort      i;
    ubyte       delay_timer;
    ubyte       sound_timer;

    ubyte       key[16];

    ushort      stack[STACK_LVL];
    byte        sp;
} Chip8;

Chip8 *     chip8_get_instance  (void);
void        chip8_cycle         (Chip8 *vm);
void        chip8_destroy       (Chip8 *vm);
void        chip8_load_game     (Chip8 *vm, const char *name);

#endif
