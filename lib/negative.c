#include <stdio.h>

void negative(unsigned char *buf, int width, int height, short bytes_pixel) {

    int i;

    // iterate through all pixels
    for (i=0; i<width*height*bytes_pixel; i++) {
        buf[i] = 255-buf[i]; 
    }
  
}