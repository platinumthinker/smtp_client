#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <sys/epoll.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
/* #include "dbg.h" */

int use_stdout = 1;
void view_help(char *file_name);
#endif //MAIN_H
