#include "dbg.h"

void setup_debug(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strncmp("-d", argv[i], 3) == 0) {
            debug_val = 1;
            break;
        }
    }
    dbg("Debug on!\n");
}


void dbg(const char *fmt, ...)
{
    if (debug_val) {
        va_list args;
        va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        va_end(args);
    }
}
