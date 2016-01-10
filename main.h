#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>
#include "dbg.h"

#define FILES_MAX 256
#define ADDRESSES_MAX 256
#define BUFFER_READ 1024
#define ever (;;)

typedef struct _RESP{
    int ret_code;
    char *msg;
} response;


void free_mem(int file_count, char **files,
        int address_count,    char **addresses,
        int address_flag,     char *server_address,
        int port_flag,        char *server_port,
        int use_stdout,       char *stdout_str);
void parse_arg(int argc,   char **argv,
        int *file_count,    char **files,
        int *address_count, char **addresses,
        int *address_flag,  char **server_address,
        int *port_flag,     char **server_port,
        int *use_stdout,    char **stdout_str);
void view_help(char *file_name);
int init_connect(char *server_address, char *server_port);
response read_from_server(int socket);

#endif //MAIN_H
