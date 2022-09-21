#include <stdio.h>

void properties(unsigned char *buf, int width, int height) {

    int i, min, max;

    min = max = buf[0];

    for (i=1; i<width*height; i++) {
        if (buf[i] < min) min = buf[i];
        if (buf[i] > max) max = buf[i];
    }

    printf("\nMax color: %d",max);
    printf("\nMin color: %d",min);

}