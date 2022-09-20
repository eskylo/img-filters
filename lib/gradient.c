#include <stdio.h>

void gradient(unsigned char *buf, int width, int height) {

    int i, j, k;

    for (i=0; i<width; i++) {
        for (j=0; j<height; j++) {
            k = buf[j*height+i]-i*255/width;
            if (k<0) k=0;
            buf[j*height+i] = k;
        }
    }
  
}