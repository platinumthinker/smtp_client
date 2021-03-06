#include "main.h"

int main(int argc, char **argv) {
    int address_count = 1, file_count = 0, show_help = 0,
        address_flag = 0, port_flag = 0, use_stdout = 0, use_pass = 0;
    char **addresses, **files, *stdout_str = NULL, *pass,
         *server_address, *server_port;
    addresses = (char **) malloc(ADDRESSES_MAX * sizeof(char *));
    files = (char **) malloc(FILES_MAX * sizeof(char *));

    parse_arg(argc, argv, &file_count, files, &address_count, addresses,
        &address_flag, &server_address, &port_flag, &server_port,
        &use_stdout, &stdout_str, &use_pass, &pass);

    int socket = init_connect(server_address, server_port);
    test_result(socket > 0);

    response rsp;

    // Hello from server
    dbg("===========================================================\n");
    rsp = read_from_server(socket);
    test_result (rsp.ret_code == 220);
    test_result (send_to_server(socket, "HELO", "think-destop") > 0);
    rsp = read_from_server(socket);
    test_result (rsp.ret_code == 250);

    if (use_pass == 1) {
        char *plain = calloc(strlen(addresses[0]) + strlen(pass) + 2, sizeof(char));
        sprintf(plain, "%s %s", addresses[0], pass);
        char *plain_enc = encode(plain);
        free(plain);
        plain = calloc(strlen(plain_enc) + 7, sizeof(char));
        sprintf(plain, "PLAIN %s", plain_enc);
        send_to_server(socket, "AUTH", plain);
        rsp = read_from_server(socket);
        /* // Test authentication success */
        test_result (rsp.ret_code == 235);

        free(plain);
        free(plain_enc);
    }

    addresses[0] = realloc(addresses[0], strlen(addresses[0]) + 10);
    char *buf_from = calloc(strlen(addresses[0]) + 1, sizeof(char));
    strcpy(buf_from, addresses[0]);
    sprintf(addresses[0], "FROM: <%s>", buf_from);
    free(buf_from);

    send_to_server(socket, "MAIL", addresses[0]);
    rsp = read_from_server(socket);
    /* test_result (rsp.ret_code == 250); */

    int sender_count = 0;
    for (int i = 1; i < address_count; i++) {
        send_to_server(socket, "RCPT", addresses[i]);
        rsp = read_from_server(socket);
        if (rsp.ret_code == 250)
            sender_count++;
    }

    /* test_result (sender_count > 0); */

    if (use_stdout == 1) {
        send_to_server(socket, "DATA", "");
        rsp = read_from_server(socket);
        /* test_result (rsp.ret_code == 354); */
        send_body_text(socket, addresses, address_count, "Subject", stdout_str);
        rsp = read_from_server(socket);
    }

    send_to_server(socket, "QUIT", "");
    rsp = read_from_server(socket);
    dbg("===========================================================\n");

    free_mem(file_count, files, address_count, addresses,
        address_flag, server_address, port_flag, server_port,
        use_stdout, stdout_str);
    close(socket);

    return 0;
}
