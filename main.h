#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void view_help(char *file_name);
int init_connect(char *server_address, char *server_port);
#endif //MAIN_H
