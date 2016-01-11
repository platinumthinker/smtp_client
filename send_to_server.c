#include "main.h"

int send_to_server(int socket, char *cmd, char *msg) {
    dbg("C: %s %s\n", cmd, msg);
    size_t len = 4 + 1 + strlen(msg) + 2;
    len = (len == 7) ? 6 : len;
    char *send_buf = calloc(len + 1, sizeof(char));
    send_buf = strcat(send_buf, cmd);
    if (len > 6) {
        send_buf = strcat(send_buf, " ");
        send_buf = strcat(send_buf, msg);
    }
    send_buf = strcat(send_buf, "\r\n");
    int ret = write(socket, send_buf, len);
    /* free(send_buf); */
    return ret;
}

int send_body_text(int socket, char **addresses, int address_count,
        char *subject, char *msg) {
    for (int i = 0; i < address_count; i++) {
        dbg("C: %s\n", addresses[i]);
        int len = strlen(addresses[i]) + 2;
        char *addr_buf = calloc(len + 1, sizeof(char));
        sprintf(addr_buf, "%s\r\n", addresses[i]);
        if (write(socket, addr_buf, len) <= 0) {
            dbg("Don't send: %s\n", addresses[i]);
        }
        free(addr_buf);
    }
    size_t len = 9 + strlen(subject) + 2;
    char *subj_buf = calloc(len + 1, sizeof(char));
    sprintf(subj_buf, "Subject: %s\r\n", subject);
    dbg("C: Subject: %s\n", subject);
    write(socket, subj_buf, len);
    free(subj_buf);
    len = strlen(msg) + 2;
    subj_buf = calloc(len + 1, sizeof(char));
    sprintf(subj_buf, "%s\r\n", msg);
    dbg("C: %s\n", msg);
    write(socket, subj_buf, len);
    write(socket, ".\r\n", 3);

    return 0;
}
