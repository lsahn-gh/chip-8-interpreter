#ifndef TYPES_H
#define TYPES_H

#if __STDC_VERSION__ >= 199901L /* C99 std */
# include <stdint.h>
# include <stdbool.h>
#else
# error "The project must be compiled at least C99 and above."
#endif

typedef unsigned char       uchar;
typedef char                byte;
typedef unsigned char       ubyte;
typedef unsigned short      ushort;
typedef unsigned int        uint;

#define BYTE(_expr)         (byte)_expr
#define UBYTE(_expr)        (ubyte)_expr
#define SHORT(_expr)        (short)_expr
#define USHORT(_expr)       (ushort)_expr

#endif
