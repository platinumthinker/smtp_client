#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int debug;

void setup_debug(int argc, char **argv);
void dbg(const char *fmt, ...);

#endif //DBG_H
