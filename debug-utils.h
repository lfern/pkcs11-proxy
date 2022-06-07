/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* debug-utils.h - 

   
*/

#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include "config.h"
#include <stdio.h>

void tohex(unsigned char * in, size_t insz, char * out, size_t outsz);
void debug_print_mesg(char* prefix, unsigned char* buf, size_t buf_size, unsigned char* buf2, size_t buf2_size);

#endif /* DEBUG_UTILS_H */