#include "utils.h"
#include "macros.h"

#include <time.h>

/* Return true if success, or false on failure */
bool
set_zero_fast (void *arr,
               uint len     /* N bytes */)
{
    ubyte *parr = arr;

    while ( len >= 16 ) {
        uint64_t * temp = (uint64_t *)parr;
        temp[0] = 0;
        temp[1] = 0;
        len -= 16;
        parr += 16;
    }
    if ( len >= 8 ) {
        *(uint64_t *)parr = 0;

        len -= 8;
        parr += 8;
    }
    if ( len >= 4 ) {
        *(uint32_t *)parr = 0;

        len -= 4;
        parr += 4;
    }
    if ( len >= 2 ) {
        *(uint16_t *)parr = 0;

        len -= 2;
        parr += 2;
    }
    if ( len >= 1 ) {
        *(uint8_t *)parr = 0;

        len -= 1;
        parr += 1;
    }

    if (len != 0) {
        warn_at_line ("len is not equals to 0!");
        return false;
    }

    return true;
}

bool
copy_fast (void *dst,
           void *src,
           uint len     /* N bytes */)
{
    ubyte *pdst = dst;
    ubyte *psrc = src;

    while ( len >= 8 ) {
        *(uint64_t *)pdst = *(uint64_t *)psrc;

        len -= 8;
        pdst += 8;
        psrc += 8;
    }
    if ( len >= 4 ) {
        *(uint32_t *)pdst = *(uint32_t *)psrc;

        len -= 4;
        pdst += 4;
        psrc += 4;
    }
    if ( len >= 2 ) {
        *(uint16_t *)pdst = *(uint16_t *)psrc;

        len -= 2;
        pdst += 2;
        psrc += 2;
    }
    if ( len >= 1 ) {
        *(uint8_t *)pdst = *(uint8_t *)psrc;

        len -= 1;
        pdst += 1;
        psrc += 1;
    }

    if ( len != 0 ) {
        warn_at_line ("len is not equals to 0!");
        return false;
    }

    return true;
}

/* Unstable version */
ubyte
get_random (void)
{
    static bool init = false;

    if ( !init ) {
        time_t t;
        srand ((unsigned)time (&t));
        init = true;
    }

    return UBYTE (rand () % 256);
}
