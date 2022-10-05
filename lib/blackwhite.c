#include <stdio.h>

void blackwhite(unsigned char *buf, int width, int height, unsigned char threshold) {

    int i;

    for (i=0; i<width*height; i++) {
        if (buf[i]<threshold) buf[i] = 0;
        else buf[i] = 255;
    }

}