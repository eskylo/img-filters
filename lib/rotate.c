#include <stdlib.h>

void rotate(unsigned char *buf, int width, int height) {

    unsigned char *tmp_buf;
    int i;

    tmp_buf = (unsigned char *) malloc(width*height);

    for (i=0; i<width*height; i++) {
        tmp_buf[i] = buf[width*height-i-1]; 
    }

    for (i=0; i<width*height; i++) {
        buf[i] = tmp_buf[i]; 
    }
}