#include "chip8.h"
#include "opcode.h"
#include "macros.h"
#include "utils.h"

/*
 * Please see CHIP-8 documentations in further details.
 */ 
static bool
_decode_opcode (Chip8 *vm)
{
    ushort opcode = vm->opcode;

    if (IS_0nnn (opcode))
    {
        /* XXX: only used on the old computers
         * which chip-8 was originally implemented.
         *
         * Same as 1nnn op? who knows. */
        ushort location = opcode & 0x0FFF;
        vm->pc = location;
    }

    /* Clear the display */
    elif (IS_00E0 (opcode))
    {
        if ( !set_zero_fast (vm->gfx, SCREEN) )
            die_at_line ("Failed to set zero.");
    }

    /* Return from a subroutine */
    elif (IS_00EE (opcode))
    {
        if (vm->sp < 0)
            die_at_line ("There is no subroutine to return.");

        vm->pc = vm->stack[vm->sp];

        if (vm->sp >= 0)
            vm->sp -= 1;
    }

    /* Jump to location nnn */
    elif (IS_1nnn (opcode))
    {
        ushort location = opcode & 0x0FFF;
        vm->pc = location;
    }

    /* Call subroutine at nnn */
    elif (IS_2nnn (opcode))
    {
        if (vm->sp >= STACK_LVL-1)
            die_at_line ("All the buckets of stack are full now, so die!");

        vm->sp += 1;
        vm->stack[vm->sp] = vm->pc;

        vm->pc = opcode & 0x0FFF;
    }

    /* Skip next instruction if Vx == kk */
    elif (IS_3xkk (opcode))
    {
        ubyte kk = UBYTE (opcode & 0x00FF);
        Register vx = GET_V (opcode, R8);

        if ( vm->V[vx] == kk )
            vm->pc += 2;
    }

    /* Skip next instruction if Vx != kk */
    elif (IS_4xkk (opcode))
    {
        ubyte kk = UBYTE (opcode & 0x00FF);
        Register vx = GET_V (opcode, R8);

        if ( vm->V[vx] != kk )
            vm->pc += 2;
    }

    /* Skip next instruction if Vx == Vy */
    elif (IS_5xy0 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        if ( vm->V[vx] == vm->V[vy] )
            vm->pc += 2;
    }

    /* Set Vx = kk */
    elif (IS_6xkk (opcode))
    {
        ubyte kk = UBYTE (opcode & 0x00FF);
        Register vx = GET_V (opcode, R8);

        vm->V[vx] = kk;
    }

    /* Set Vx = Vx + kk */
    elif (IS_7xkk (opcode))
    {
        ubyte kk = UBYTE (opcode & 0x00FF);
        Register vx = GET_V (opcode, R8);

        vm->V[vx] += kk;
    }

    /* Set Vx = Vy */
    elif (IS_8xy0 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[vx] = vm->V[vy];
    }

    /* Set Vx = Vx OR Vy */
    elif (IS_8xy1 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[vx] |= vm->V[vy];
    }

    /* Set Vx = Vx AND Vy */
    elif (IS_8xy2 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[vx] &= vm->V[vy];
    }

    /* Set Vx = Vx XOR Vy */
    elif (IS_8xy3 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[vx] ^= vm->V[vy];
    }

    /* Set Vx = Vx + Vy, set VF = carry */
    elif (IS_8xy4 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);
        ushort result;
        
        result = vm->V[vx] + vm->V[vy];

        /*
         * If the result is greater than 8 bits (i.e., > 255,)
         * VF is set to 1, otherwise 0.
         * Only the lowest 8 bits of the result are kept, and
         * stored in Vx.
         * 
         * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#8xy4
         */
        vm->V[VF] = (result > 255) ? 1 : 0;
        vm->V[vx] = UBYTE (result & 0x00FF);
    }

    /* Set Vx = Vx - Vy, set VF = NOT borrow */
    elif (IS_8xy5 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[VF] = (vm->V[vx] > vm->V[vy]) ? 1 : 0;
        vm->V[vx] -= vm->V[vy];
    }

    /* Set Vx = Vx SHR 1 */
    elif (IS_8xy6 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->V[VF] = (vm->V[vx] & 0x01) ? 1 : 0;
        vm->V[vx] >>= 1;
    }

    /* Set Vx = Vy - Vx, set VF = NOT borrow */
    elif (IS_8xy7 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        vm->V[VF] = (vm->V[vy] > vm->V[vx]) ? 1 : 0;
        vm->V[vx] = vm->V[vy] - vm->V[vx];
    }

    /* Set Vx = Vx SHL 1 */
    elif (IS_8xyE (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->V[VF] = (vm->V[vx] & 0x80) ? 1 : 0;
        vm->V[vx] <<= 1;
    }

    /* Skip next instruction if Vx != Vy */
    elif (IS_9xy0 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        if ( vm->V[vx] != vm->V[vy] )
            vm->pc += 2;
    }

    /* Set I = nnn */
    elif (IS_Annn (opcode))
    {
        ushort nnn = (opcode & 0x0FFF);
        vm->I = nnn;
    }

    /* Jump to location nnn + V0 */
    elif (IS_Bnnn (opcode))
    {
        ushort nnn = (opcode & 0x0FFF);
        vm->pc = nnn + vm->V[V0];
    }

    /* Set Vx = random byte AND kk */
    elif (IS_Cxkk (opcode))
    {
        ubyte kk = UBYTE (opcode & 0x00FF);
        Register vx = GET_V (opcode, R8);

        vm->V[vx] = (get_random () & kk);
    }

    /* Display n-byte */
    elif (IS_Dxyn (opcode))
    {
        /*
         * Display n-byte sprite starting at memory location I
         * at (Vx, Vy), set VF = collision
         * 
         * The interpreter reads n bytes from memory, starting
         * at the address stored in I. These bytes are then displayed
         * as sprites on screen at coordinates (Vx, Vy). Sprites are
         * XORed onto the existing screen. If this causes any pixels
         * to be erased, VF is set to 1, otherwise it is set to 0.
         * 
         * See reference for the details.
         */

        Register vx = GET_V (opcode, R8);
        Register vy = GET_V (opcode, R4);

        ubyte pos_x = vm->V[vx];
        ubyte pos_y = vm->V[vy];

        ushort addr = vm->memory[vm->I];

        /* TODO implement the rest of code */

    }

    /*
     * Skip next instruction
     * if key with the value of Vx is pressed
     */
    elif (IS_Ex9E (opcode))
    {
        Register vx = GET_V (opcode, R8);

        /* TODO implement the rest of code */
    }

    /*
     * Skip next instruction
     * if key with the value of Vx is not pressed
     */
    elif (IS_ExA1 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        /* TODO implement the rest of code */
    }

    /* Set Vx = delay timer value */
    elif (IS_Fx07 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->V[vx] = vm->delay_timer;
    }

    /* Wait for a key press, store the value of the key in Vx */
    elif (IS_Fx0A (opcode))
    {
        /* TODO implement the rest of code */
    }

    /* Set delay timer = Vx */
    elif (IS_Fx15 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->delay_timer = vm->V[vx];
    }

    /* Set sound timer = Vx */
    elif (IS_Fx18 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->sound_timer = vm->V[vx];
    }

    /* Set I = I + Vx */
    elif (IS_Fx1E (opcode))
    {
        Register vx = GET_V (opcode, R8);

        vm->I += vm->V[vx];
    }

    /* Set I = location of sprite for digit Vx */
    elif (IS_Fx29 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        /* TODO implement the rest of code */
    }

    /* Store BCD representation of Vx in memory location I, I+1, and I+2 */
    elif (IS_Fx33 (opcode))
    {
        Register vx = GET_V (opcode, R8);

        /* TODO implement the rest of code */
    }

    /* Store registers V0 through Vx in memory starting at location I */
    elif (IS_Fx55 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        ubyte * dst = (vm->memory + vm->I);
        ubyte * src = vm->V;

        if ( !copy_fast (dst, src, vx + 1) )
            die_at_line ("Failed to copy the registers to the memory");
    }

    /* Read registers V0 through Vx from memory starting at location I */
    elif (IS_Fx65 (opcode))
    {
        Register vx = GET_V (opcode, R8);
        ubyte * dst = vm->V;
        ubyte * src = (vm->memory + vm->I);

        if ( !copy_fast (dst, src, vx + 1) )
            die_at_line ("Failed to copy the memory to the registers");
    }

    else {
        /* Decoding error */
        return false;
    }

    return true;
}

bool
chip8_decode_opcode (Chip8 *vm)
{
    /* Add NULL check */

    _decode_opcode (vm);
}
