#include "main.h"

void view_help(char *programm_name) {
    printf("Usage %s [OPTION...]\n", programm_name),
    printf("  -a\tsender address\n"),
    printf("  -f\tadd attachment file\n"),
    printf("  -i\tget message from stdout\n"),
    printf("  -d\tprint debug output\n"),
    printf("  -h\tprint this message\n");
}

int main(int argc, char **argv) {
    setup_debug(argc, argv);

    int address_count = 0, file_count = 0;
    char **addresses, **files, **stdout;

    dbg("Arguments:\n");
    for (int i = 1; i < argc; i++) {
        dbg("%s\n", argv[i]);
    }

    dbg("\nStdout:\n");
    char buf[256];
    while (fgets(buf, 255, stdin) != 0) {
        buf[255] = '\0';
        dbg("%s\n", buf);
    }
    dbg("\nEnd stdout\n"),

    view_help(argv[0]);
}
