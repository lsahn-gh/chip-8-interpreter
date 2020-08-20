#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>

#define ARR_SIZE(arr)   (sizeof(arr)/sizeof((arr)[0]))

#define elif else if    /* As honest as Elif */


#define NONE (void)0

#define _ERR_CODE(_code, ...) \
    do { \
        fprintf(stderr, __VA_ARGS__); \
        { #_code ; } \
    } while (0)

#define die(...) \
    _ERR_CODE(exit(1), __VA_ARGS__)

#define die_at_line(message) \
    die("LINE %s :: " message "\n", __LINE__)

#define warn(...) \
    _ERR_CODE(NONE, __VA_ARGS__)

#define warn_at_line(message) \
    warn("LINE %s :: " message "\n", __LINE__)

#define warn_ret_at_line(msg,ret_bool)   \
    _ERR_CODE(return, "LINE %s :: " message "\n", __LINE__)


/*
#if defined (__GNUC__)
static void cleanup_free (void *p)
{
    free(*(void**) p);
}
# define    autoptr(type)   __attribute__((cleanup(cleanup_free))) type *
#else
# define    autoptr(type)   type *
#endif
*/

#endif
