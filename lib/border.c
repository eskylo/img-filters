#include <stdio.h>

void border(unsigned char *buf, int width, int height, int color, int bsize) {

    int i, j;

    // bottom-top border
    for (i=0; i<width*bsize; i++) {
        buf[i] = color; 
        buf[width*height-i] = color; 
    }
  
    // side border
    for (i=0; i<height; i++) {
        for (j=0; j<bsize; j++) {
            buf[i*width+j] = color;
            buf[i*width+width-j-1] = color;
        }
    }

}