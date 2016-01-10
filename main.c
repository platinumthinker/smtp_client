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

void free_mem(int file_count, char **files, int address_count, char **addresses,
        int address_flag, char *server_address,
        int port_flag, char *server_port,
        int use_stdout, char *stdout_str) {

    for (int i = 0; i < file_count; i++)
        free(files[i]);
    free(files);

    for (int i = 0; i < address_count; i++)
        free(addresses[i]);
    free(addresses);

    if (address_flag)
        free(server_address);
    if (port_flag)
        free(server_port);
    if(use_stdout)
        free(stdout_str);

}

int main(int argc, char **argv) {
    setup_debug(argc, argv);

    int address_count = 0, file_count = 0, show_help = 0,
        address_flag = 0, port_flag = 0, use_stdout = 0;

    char **addresses, **files, *stdout_str = NULL, *server_address, *server_port;

    addresses = (char **) malloc(ADDRESSES_MAX * sizeof(char *));
    files = (char **) malloc(FILES_MAX * sizeof(char *));

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
                addresses[address_count] = (char *) malloc(strlen(argv[i + 1]));
                strcpy(addresses[address_count], argv[i + 1]);
                address_count++; i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-f", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                files[file_count] = (char *) malloc(strlen(argv[i + 1]));
                strcpy(files[file_count], argv[i + 1]);
                file_count++; i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-s", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                server_address = malloc(strlen(argv[i + 1]));
                strcpy(server_address, argv[i + 1]);
                address_flag = 1;
                i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-p", argv[i], 3) == 0) {
            if (i == argc - 1) {
                dbg("Invalid argument '%s'\n", argv[i]);
                show_help = 1;
                break;
            } else {
                server_port = malloc(strlen(argv[i + 1]));
                strcpy(server_port, argv[i + 1]);
                port_flag = 1;
                i++;
                dbg("%s", argv[i]);
            }
        } else if (strncmp("-i", argv[i], 3) == 0) {
            use_stdout = 1;
        } else if (strncmp("-h", argv[i], 3) == 0) {
            show_help = 1;
        }
        dbg("\n");
    }

    if (!address_flag)
        server_address = "aspmx.l.google.com";
    if (!port_flag)
        server_port= "25";

    if (show_help) {
        view_help(argv[0]);
        return EXIT_SUCCESS;
    }

    dbg("===========================================================\n\n");
    if (use_stdout) {
        char buf[256] = {'\0'};
        int stdout_count = 0;
        while (fgets(buf, 254, stdin) > 0) {
            stdout_count += strlen(buf);
            stdout_str = realloc(stdout_str, stdout_count);
            strcat(stdout_str, buf);
        }
        dbg("\nStdout:\n%sEnd stdout\n\n", stdout_str);
        dbg("===========================================================\n\n");
    }

    int socket = init_connect(server_address, server_port);
    response r = read_from_server(socket);
    if (socket > 0) {
        /* send_message(socket, address_count, addresses, file_count, files, stdout); */
        close(socket);
    }


    free_mem(file_count, files, address_count, addresses,
        address_flag, server_address, port_flag, server_port,
        use_stdout, stdout_str);

    return 0;
}
