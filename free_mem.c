#include "main.h"

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
