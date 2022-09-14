#include <stdio.h>

void negative(unsigned char *buf, int width, int height) {

    int i;

    // iterate through all pixels
    for (i=0; i<width*height; i++) {
        buf[i] = 255-buf[i]; 
    }
  
}