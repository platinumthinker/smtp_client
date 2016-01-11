#include "base64.h"

char *encode(char *input) {
    BIO *b64 = NULL, *bmem = NULL;
    BUF_MEM *bptr = NULL;
    char *output = NULL;

    b64 = BIO_new((BIO_METHOD *)BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, strlen(input) + 1);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    output = (char *) calloc (bptr->length + 1, sizeof(char));
    strncat(output, bptr->data, bptr->length);

    BIO_free_all(b64);
    return output;
}
