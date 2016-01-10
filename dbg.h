#pragma once
#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int debug_val = 0;

void setup_debug(int argc, char **argv);
void dbg(const char *fmt, ...);

#endif //DBG_H
