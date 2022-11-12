#include <stdio.h>

void border(unsigned char *buf, int width, int height, short bytes_pixel, unsigned char color, int bsize) {

    int i, j, k;

    // bottom-top border
    for (i=0; i<width*bsize*bytes_pixel; i++) {
        buf[i] = color; 
        buf[width*height*bytes_pixel-i-1] = color; 
    }
  
    // side border
    for (i=0; i<height; i++) {
        for (j=0; j<bsize; j++) {
            //for (k=0; k<bytes_pixel; k++) {
                buf[i*width+j] = color;
                buf[i*width+width-j-1] = color;
            //}
        }
    }

}