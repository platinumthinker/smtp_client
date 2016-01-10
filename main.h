#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/epoll.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include "dbg.h"

#define FILES_MAX 256
#define ADDRESSES_MAX 256

int use_stdout = 0;
void view_help(char *file_name);
#endif //MAIN_H
