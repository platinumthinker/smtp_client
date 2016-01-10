#include "main.h"

int init_connect(char *server_address, char *server_port) {
    int my_socket;
    char **pointer;
    char answer[INET_ADDRSTRLEN];
    struct hostent *res_host;
    struct sockaddr_in address;

    dbg("Server parameters: %s:%s\n", server_address, server_port);

    res_host = gethostbyname(server_address);

    if (res_host == NULL) {
        perror("error gethostbyname\n");
        return -1;
    }

    dbg("Server official name: %s\n", res_host->h_name);

    for(pointer = res_host->h_addr_list; *pointer; pointer++) {
        inet_ntop(AF_INET, (void *)*pointer, answer, sizeof(answer));
        dbg("IP address: %s\n", answer);
        my_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(my_socket < 0) {
            perror("socket()");
            return -1;
        }

        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(atoi(server_port));

        memmove(&address.sin_addr, *pointer, sizeof(&address.sin_addr));

        if(connect(my_socket, (struct sockaddr*)&address, sizeof(address))) {
            perror("connect()");
            return -1;
        }

        dbg("connection established on file descriptor %d\n\n", my_socket);
        return my_socket;
    }
}
