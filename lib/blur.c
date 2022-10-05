#include <stdio.h>

void blur(unsigned char *buf, int width, int height) {

    float kernel[3][3] = {{1/9,1/9,1/9},{1/9,1/9,1/9},{1/9,1/9,1/9}};
    unsigned char img[width][height], out[width][height];
    int i, j, k;

    k = 0;

    for (i = 0; i<width; i++){
        for (j = 0; j<height; j++){
            img[i][j] = buf[k];
            k++;            
        }
    }

    for (i = 1; i<width-1; i++){
        for (j = 1; j<height-1; j++){
            out[i][j] = (
                 img[i-2][j-2]*1+img[i-2][j-1]*4 +img[i-2][j]*7 +img[i-2][j+1]*4 +img[i-2][j+2]*1
                +img[i-1][j-2]*4+img[i-1][j-1]*16+img[i-1][j]*26+img[i-1][j+1]*16+img[i-1][j+2]*4
                +img[i+0][j-2]*7+img[i+0][j-1]*26+img[i+0][j]*41+img[i+0][j+1]*26+img[i+0][j+2]*7
                +img[i+1][j-2]*4+img[i+1][j-1]*16+img[i+1][j]*26+img[i+1][j+1]*16+img[i+1][j+2]*4
                +img[i+2][j-2]*1+img[i+2][j-1]*4 +img[i+2][j]*7 +img[i+2][j+1]*4 +img[i+2][j+2]*1
            )/273;
        }
    }

    k = 0;

    for (i = 0; i<width; i++){
        for (j = 0; j<height; j++){
            buf[k] = out[i][j];
            k++;            
        }
    }

}