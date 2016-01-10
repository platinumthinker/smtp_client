#include "main.h"

response read_from_server(int socket) {
    char buffer[BUFFER_READ + 1] = {'\0'}, *find = NULL, *resp = NULL;
    ssize_t rc = 0, point = 0;
    for ever {
        rc = read(socket, buffer, BUFFER_READ);

        if (rc <= 0)
            break;

        point += rc;
        resp = (char *)realloc(resp, point);
        strcat(resp, buffer);
        find = index(resp, '\r');
        if (find > 0) {
            find = index(find, '\n');
            if (find > 0) {
                char *str = (char *)malloc(strlen(resp));
                int ret = -1;
                sscanf(resp, "%d %[^\r^\n] \r\n", &ret, str);
                free(resp);

                dbg("S: %d %s\n", ret, str);
                return (response){.ret_code = ret, .msg = str};
            }
        }
    }

    return (response){.ret_code = -1};
}
