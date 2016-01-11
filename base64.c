#include "base64.h"

char *encode(char *input) {
    BIO *b64 = NULL, *bmem = NULL;
    BUF_MEM *bptr = NULL;
    char *output = NULL;
    unsigned int i, len = strlen(input), len_esc = 0;
    char *input_esc = (char *) calloc ((len + 1) * 2 + 3, sizeof(char));
    input_esc[len_esc++] = '\0';
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            input_esc[len_esc++] = '\000';
        }
        else {
            input_esc[len_esc++] = input[i];
        }
    }

    b64 = BIO_new((BIO_METHOD *)BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input_esc, len_esc);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    output = (char *) calloc (bptr->length + 1, sizeof(char));
    strncat(output, bptr->data, bptr->length);

    BIO_free_all(b64);
    return output;
}
