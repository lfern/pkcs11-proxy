
#include "debug-utils.h"
#include "gck-rpc-private.h"


void tohex(unsigned char * in, size_t insz, char * out, size_t outsz)
{
    unsigned char * pin = in;
    const char * hex = "0123456789ABCDEF";
    char * pout = out;
    for(; pin < in+insz; pout +=3, pin++){
        pout[0] = hex[(*pin>>4) & 0xF];
        pout[1] = hex[ *pin     & 0xF];
        pout[2] = ':';
        if (pout + 3 - out > outsz){
            /* Better to truncate output string than overflow buffer */
            /* it would be still better to either return a status */
            /* or ensure the target buffer is large enough and it never happen */
            break;
        }
    }
    pout[-1] = 0;
}

void debug_print_mesg(char* prefix, unsigned char* buf, size_t buf_size, unsigned char* buf2, size_t buf2_size)
{
    char b[4096];
    size_t size = 0;
    for (int i=0; i < buf_size; i++) {
        size = size << 8;
        size = size | buf[i];
    }

    tohex(buf, buf_size, b, 4090);
    gck_rpc_debug("%s bytes lenght(%d), %s", prefix, size, b);
    tohex(buf2, buf2_size, b, 4090);
    gck_rpc_debug("%s buffer %s", prefix, b);
}

void debug_print_attr_recv (EggBuffer *buffer, CK_ATTRIBUTE_PTR template, CK_ULONG count) 
{
    char b[4096];
    tohex(buffer->buf, buffer->len, b, 4090);
    gck_rpc_debug("-------> received %s", b);
    for (int i=0;i<count;i++){
        gck_rpc_debug("-------> decoding %x %d", template[i].pValue, template[i].ulValueLen);
        if (template[i].pValue) {
            tohex(template[i].pValue, template[i].ulValueLen, b, 4090);
            gck_rpc_debug("-------> %x", template[i].type);
            gck_rpc_debug("-------> (%d) %s",template[i].ulValueLen, b);
        }
    }
}
