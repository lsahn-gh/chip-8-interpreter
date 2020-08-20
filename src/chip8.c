#include "chip8.h"
#include "opcode.h"
#include "macros.h"
#include "utils.h"

static void
_chip8_fetch (Chip8 *vm)
{
    ushort pc = vm->pc;
    ubyte *mem = vm->memory;

    vm->opcode = mem[pc] << 8 | mem[pc+1];
    vm->pc = pc + 2;

    if ( !chip8_decode_opcode (vm) ) {

    }
}

static void
_chip8_decode (Chip8 *vm)
{

}

static void
_chip8_execute (Chip8 *vm)
{

}

static void
_chip8_initialize (Chip8 *vm)
{
    if ( !set_zero_fast (vm, sizeof(Chip8)) )
        die_at_line ("Failed to set zero");

    /* Start address of chip8 programs */
    vm->pc = 0x200;
    vm->sp = -1;
}

static void
_chip8_finalize (Chip8 *vm)
{

}

static Chip8 *
chip8_new (void)
{
    Chip8 *ptr;

    if ( (ptr = malloc(sizeof(Chip8)) ) == NULL)
        return NULL;

    _chip8_initialize (ptr);

    return ptr;
}

Chip8 *
chip8_get_instance (void)
{
    /* Singleton instance */
    static Chip8 *instance = NULL;

    if (instance == NULL)
        instance = chip8_new ();

    return instance;
}

void
chip8_destroy (Chip8 *vm)
{
    free (vm);
}

void
chip8_cycle (Chip8 *vm)
{
    /* One cycle of it */

    _chip8_fetch (vm);
    _chip8_decode (vm);
    _chip8_execute (vm);
}

void
chip8_load_game (Chip8 *vm, const char *name)
{

}
