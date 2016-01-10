#include "main.h"

int main(int argc, char **argv) {
    int address_count = 0, file_count = 0, show_help = 0,
        address_flag = 0, port_flag = 0, use_stdout = 0;
    char **addresses, **files, *stdout_str = NULL, *server_address, *server_port;
    addresses = (char **) malloc(ADDRESSES_MAX * sizeof(char *));
    files = (char **) malloc(FILES_MAX * sizeof(char *));

    parse_arg(argc, argv, &file_count, files, &address_count, addresses,
        &address_flag, &server_address, &port_flag, &server_port,
        &use_stdout, &stdout_str);

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
