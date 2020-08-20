#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

bool set_zero_fast (void *arr, uint len);
bool copy_fast (void *dst, void *src, uint len);
ubyte get_random (void);

#endif
