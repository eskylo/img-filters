#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bmp.h"
#include "showheader.h"

/*
   Header:
   offset	size	description
   0		2	signature, must be 4D42 hex
   2		4	size of BMP file in bytes (unreliable)
   6		2	reserved, must be zero
   8		2	reserved, must be zero
   10		4	offset to start of image data in bytes
   14		4	size of BITMAPINFOHEADER structure, must be 40
   18		4	image width in pixels
   22		4	image height in pixels
   26		2	number of planes in the image, must be 1
   28		2	number of bits per pixel (1, 4, 8, or 24)
   30		4	compression type (0=none, 1=RLE-8, 2=RLE-4)
   34		4	size of image data in bytes (including padding)
   38		4	horizontal resolution in pixels per meter (unreliable)
   42		4	vertical resolution in pixels per meter (unreliable)
   46		4	number of colors in image, or zero
   50		4	number of important colors, or zero
*/

int main(void) {

	bmpheader hd;
	bmpinfoheader infohd;

	unsigned char header[HDRBMP] = {0};	/* To store the image header */
	unsigned char colorTable[HBMPCT] = {0};	/* To store the colorTable, if it exists */

	char fname[] = "./lena512.bmp";
	char out[] = "./saida.bmp";
	unsigned char *buf;
	int option, bsize;

	FILE *streamIn, *fo;

	unsigned int i;
	double sz;

	/* Display menu */
	printf("Choose a filter:\n\n");
	printf("[1] White Border\n");
	printf("[2] Black Border\n");
	printf("[3] Negative\n");
	printf("[4] Gradient\n");
	scanf("%d", &option);

	streamIn = fopen(fname, "rb");	/* Open the file */
	if (streamIn == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < HDRBMP; i++) {
		header[i] = getc(streamIn);	/* Strip out BMP header, byte-wise */
	}

	if (gethd(&header[0], &hd)) {
	    fclose(streamIn);
	    perror("BMP header error");
	    exit(EXIT_FAILURE);
	}

	getinfohd(header, &infohd);

	/* BMP (Windows) header */
	//printf("\nBMP (Windows) header\n");
	//printhd(&hd);
	//printinfohd(&infohd);

	if (infohd.bits <= HDRBD) {
		fread(colorTable, sizeof(unsigned char), HBMPCT, streamIn);
	}

	/* Avoid invalid requests */
	if (infohd.height < 0 || infohd.width < 0)
	    perror("Overflow");

	/* Check for signed int overflow */
	if (infohd.height && infohd.width > INT_MAX / infohd.height)
	    perror("Overflow");

	sz = infohd.height * infohd.width;
	buf = (unsigned char *) malloc(sz);	/* To store the image data */

	if (buf == NULL) {
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	fread(buf, sizeof(unsigned char), sz, streamIn);

	/* Apply filter */
	if (option == 1) {/* White Border */
		printf("Enter the border size:\n\n");
		scanf("%d", &bsize);
		border(buf, infohd.width, infohd.height, 255, bsize);
	}

	if (option == 2) {/* Black Border */
		printf("Enter the border size:\n\n");
		scanf("%d", &bsize);
		border(buf, infohd.width, infohd.height, 0, bsize);
	}

	if (option == 3) /* Negative */
		negative(buf, infohd.width, infohd.height);
	
	if (option == 4) /* Gradient */
		gradient(buf, infohd.width, infohd.height);

	fo = fopen(out, "wb");	/* Open the file */
	if (fo == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	/* Write the image header to output file */
	fwrite(header, sizeof(unsigned char), HDRBMP, fo);

	if (infohd.bits <= 8) {
		fwrite(colorTable, sizeof(unsigned char), HBMPCT, fo);
	}

	fwrite(buf, sizeof(unsigned char), sz, fo);

	fclose(fo);
	fclose(streamIn);

	free(buf);
	return(EXIT_SUCCESS);
}

/* Bitmap BGR to bitmap RGB (swaping R and B values) */
/*
uint idx = 0;
unsigned char buf[];

for (idx = 0; idx < infohd->imagesize; idx += 3) { // infohd->imagesize or sz
     buf[idx]     = buf[idx] ^ buf[idx + 2];
     buf[idx + 2] = buf[idx + 2] ^ buf[idx];
     buf[idx]     = buf[idx] ^ buf[idx + 2];
}

or

typedef struct {
    unsigned char r, g, b, junk;
} COLOUR_IDX;
*/

/**************************/
/* Vers�o compacta:       */
/* *x ^= *y ^= *x^ = *y;  */
/**************************/