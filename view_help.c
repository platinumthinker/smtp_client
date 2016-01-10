#include "main.h"

void view_help(char *programm_name) {
    printf("Usage %s [OPTION...]\n", programm_name),
    printf("  -a\tsender address\n"),
    printf("  -f\tadd attachment file\n"),
    printf("  -i\tget message from stdout\n"),
    printf("  -d\tprint debug output\n"),
    printf("  -s\taddress for smtp server\n");
    printf("  -p\tport for smtp server\n");
    printf("  -h\tprint this message\n");
}
