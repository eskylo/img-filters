//#include "bmp.h"

int  gethd(unsigned char *, bmpheader *);
void getinfohd(unsigned char [], bmpinfoheader *);
void printhd(bmpheader *);
void printinfohd(bmpinfoheader *);

void border(unsigned char *buf, int width, int height, int color, int bsize);
void negative(unsigned char *buf, int width, int height);
void gradient(unsigned char *buf, int width, int height);