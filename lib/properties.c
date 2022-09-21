#include <stdio.h>
#include "bmp.h"

void min_max_color(unsigned char *buf, int width, int height) {

    int i, min, max;

    min = max = buf[0];

    for (i=1; i<width*height; i++) {
        if (buf[i] < min) min = buf[i];
        if (buf[i] > max) max = buf[i];
    }

    printf("Max color: %d\n",max);
    printf("Min color: %d\n",min);

}

void real_size(bmpheader *hd, bmpinfoheader *infohd) {

    int real_size;

    real_size = infohd->width * infohd->height * infohd->bits/8 + HDRBMP + HBMPCT;

    printf("Real size: %d\n", real_size);

    /* Compare real size with size in header */
    if (real_size == hd->size) printf("The file size in header is correct.\n");
    else printf("The file size in header is wrong.\n");

}