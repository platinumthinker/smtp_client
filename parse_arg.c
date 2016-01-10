#include "main.h"

void parse_arg(int argc,   char **argv,
        int *file_count,    char **files,
        int *address_count, char **addresses,
        int *address_flag,  char **server_address,
        int *port_flag,     char **server_port,
        int *use_stdout,    char **stdout_str) {

    setup_debug(argc, argv);

    int show_help = 0, mailbox = 0;

    dbg("\n===========================================================\n");
    dbg("Arguments:\n");
    for (int i = 1; i < argc; i++) {
        dbg("%s ", argv[i]);
        if (strncmp("-a", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                addresses[(*address_count)] = (char *) malloc(strlen(argv[i + 1]) + 8);
                sprintf(addresses[(*address_count)], "TO: <%s>", argv[i + 1]);
                (*address_count)++; i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-m", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                addresses[0] = (char *) malloc(strlen(argv[i + 1]) + 10);
                sprintf(addresses[0], "FROM: <%s>", argv[i + 1]);
                i++; mailbox = 1;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-f", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                files[(*file_count)] = (char *) malloc(strlen(argv[i + 1]));
                strcpy(files[(*file_count)], argv[i + 1]);
                (*file_count)++; i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-f", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                files[(*file_count)] = (char *) malloc(strlen(argv[i + 1]));
                strcpy(files[(*file_count)], argv[i + 1]);
                (*file_count)++; i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-s", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                (*server_address) = (char *)malloc(strlen(argv[i + 1]));
                strcpy((*server_address), argv[i + 1]);
                (*address_flag) = 1;
                i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-p", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                (*server_port) = (char *)malloc(strlen(argv[i + 1]));
                strcpy((*server_port), argv[i + 1]);
                (*port_flag) = 1;
                i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-i", argv[i], 3) == 0) {
            (*use_stdout) = 1;
        } else if (strncmp("-h", argv[i], 3) == 0) {
            show_help = 1;
        }
        dbg("\n");
    }

    if (mailbox == 0) {
        addresses[0] = (char *)malloc(25);
        sprintf(addresses[0], "FROM: <%s>", "example@example.com");
    }
    if ((*address_flag) == 0) {
        (*server_address) = (char *)malloc(19);
        strcpy((*server_address), "aspmx.l.google.com");
    }
    if ((*port_flag) == 0) {
        (*server_port) = (char *)malloc(19);
        strcpy((*server_port), "25");
    }

    if (show_help) {
        view_help(argv[0]);
        return;
    }
    dbg("===========================================================\n\n");

    dbg("===========================================================\n");
    if ((*use_stdout) != 0) {
        char buf[256] = {'\0'};
        int stdout_count = 0;
        while (fgets(buf, 254, stdin) > 0) {
            stdout_count += strlen(buf);
            (*stdout_str) = realloc((*stdout_str), stdout_count);
            (*stdout_str) = strcat((*stdout_str), buf);
        }
        dbg("Stdout:\n%sEnd stdout\n", (*stdout_str));
        dbg("===========================================================\n\n");
    }
}
