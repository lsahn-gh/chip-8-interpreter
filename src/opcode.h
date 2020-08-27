#ifndef OPCODE_H
#define OPCODE_H

#include "types.h"

#define IS_COND(_EXPR)          ((_EXPR) ? true : false)
#define AND_0x000F(_OPCODE)     (_OPCODE & 0x000F)
#define AND_0xF000(_OPCODE)     (_OPCODE & 0xF000)
#define AND_0xF00F(_OPCODE)     (_OPCODE & 0xF00F)
#define AND_0xF0FF(_OPCODE)     (_OPCODE & 0xF0FF)
#define AND_0xFFF0(_OPCODE)     (_OPCODE & 0xFFF0)

/*
 * The opcode functions are based on the link[1].
 * 
 * [1]: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1
 */

#define IS_0nnn(_OP)    IS_COND(AND_0xF000(_OP) == 0x0000)
#define IS_00E0(_OP)    IS_COND(_OP == 0x00E0)
#define IS_00EE(_OP)    IS_COND(_OP == 0x00EE)
#define IS_1nnn(_OP)    IS_COND(AND_0xF000(_OP) == 0x1000)
#define IS_2nnn(_OP)    IS_COND(AND_0xF000(_OP) == 0x2000)
#define IS_3xkk(_OP)    IS_COND(AND_0xF000(_OP) == 0x3000)
#define IS_4xkk(_OP)    IS_COND(AND_0xF000(_OP) == 0x4000)
#define IS_5xy0(_OP)    IS_COND(AND_0xF00F(_OP) == 0x5000)
#define IS_6xkk(_OP)    IS_COND(AND_0xF000(_OP) == 0x6000)
#define IS_7xkk(_OP)    IS_COND(AND_0xF000(_OP) == 0x7000)
#define IS_8xy0(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8000)
#define IS_8xy1(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8001)
#define IS_8xy2(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8002)
#define IS_8xy3(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8003)
#define IS_8xy4(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8004)
#define IS_8xy5(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8005)
#define IS_8xy6(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8006)
#define IS_8xy7(_OP)    IS_COND(AND_0xF00F(_OP) == 0x8007)
#define IS_8xyE(_OP)    IS_COND(AND_0xF00F(_OP) == 0x800E)
#define IS_9xy0(_OP)    IS_COND(AND_0xF00F(_OP) == 0x9000)
#define IS_Annn(_OP)    IS_COND(AND_0xF000(_OP) == 0xA000)
#define IS_Bnnn(_OP)    IS_COND(AND_0xF000(_OP) == 0xB000)
#define IS_Cxkk(_OP)    IS_COND(AND_0xF000(_OP) == 0xC000)
#define IS_Dxyn(_OP)    IS_COND(AND_0xF000(_OP) == 0xD000)
#define IS_Ex9E(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xE09E)
#define IS_ExA1(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xE0A1)
#define IS_Fx07(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF007)
#define IS_Fx0A(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF00A)
#define IS_Fx15(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF015)
#define IS_Fx18(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF018)
#define IS_Fx1E(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF01E)
#define IS_Fx29(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF029)
#define IS_Fx33(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF033)
#define IS_Fx55(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF055)
#define IS_Fx65(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF065)

/* Super Chip 48 instructions */
#define IS_00Cn(_OP)    IS_COND(AND_0xFFF0(_OP) == 0x00C0)
#define IS_00FB(_OP)    IS_COND(_OP == 0x00FB)
#define IS_00FC(_OP)    IS_COND(_OP == 0x00FC)
#define IS_00FD(_OP)    IS_COND(_OP == 0x00FD)
#define IS_00FE(_OP)    IS_COND(_OP == 0x00FE)
#define IS_00FF(_OP)    IS_COND(_OP == 0x00FF)
#define IS_Dxy0(_OP)    IS_COND(AND_0xF00F(_OP) == 0xD000)
#define IS_Fx30(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF030)
#define IS_Fx75(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF075)
#define IS_Fx85(_OP)    IS_COND(AND_0xF0FF(_OP) == 0xF085)

bool chip8_decode_opcode (Chip8 *vm);

#endif
