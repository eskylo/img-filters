#include <stdio.h>
#include <stdio.h>

void blur(unsigned char *buf, int width, int height) {

    float kernel[3][3] = {{1/9,1/9,1/9},{1/9,1/9,1/9},{1/9,1/9,1/9}};
    unsigned char img[width][height];
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
            img[i][j] = (img[i-1][j-1]*1/9+img[i-1][j]*1/9+img[i-1][j+1]*1/9
                        +img[i+0][j-1]*1/9+img[i+0][j]*1/9+img[i+0][j+1]*1/9
                        +img[i+1][j-1]*1/9+img[i+1][j]*1/9+img[i+1][j+1]*1/9);
        }
    }

    k = 0;

    for (i = 0; i<width; i++){
        for (j = 0; j<height; j++){
            buf[k] = img[i][j];
            k++;            
        }
    }

}