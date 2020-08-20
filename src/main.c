#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"
#include "macros.h"

int
main (int argc, char *argv[])
{
    Chip8 *vm;

    vm = chip8_get_instance ();

    chip8_load_game (vm, "pong");
    /* TODO add sigaction for SIGINT */

    while (true) {
        chip8_cycle (vm);
    }

    chip8_destroy (vm);

    return 0;
}
