#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bmp.h"
#include "showheader.h"

int gethd(unsigned char *header, bmpheader *hd) {
	hd->type = *(unsigned short int *) &header[0];			/* Magic identifier */
	/* Verify that this is a .BMP file by checking bitmap signature */
	if (hd->type != 0x4D42) {
	    return(1);
	}

	hd->size = *(unsigned int *) &header[2];			/* File size in bytes (unreliable) */
	hd->reserved1 = *(unsigned short int *) &header[6];		/* Reserved */
	hd->reserved2 = *(unsigned short int *) &header[8];		/* Reserved */
	hd->offset = *(unsigned int *) &header[10];			/* Offset to image data, bytes */
	return(0);
}

void getinfohd(unsigned char header[], bmpinfoheader *infohd) {
	infohd->size = *(unsigned int *) &header[14];			/* Header size in bytes */
	infohd->width = *(int *) &header[18];				/* Read the width from the image header */
	infohd->height = *(int *) &header[22];				/* Read the height from the image header */
	infohd->planes = *(unsigned short int *) &header[26];		/* Number of colour planes */
	infohd->bits = *(unsigned short int *) &header[28];		/* Read the bits per pixel (bitDepth) from the image header */
	infohd->compression = *(unsigned int *) &header[30];		/* Compression type */
	infohd->imagesize = *(unsigned int *) &header[34];		/* Image size in bytes */
	infohd->xresolution = *(int *) &header[38];			/* Pixels per meter (unreliable) */
	infohd->yresolution = *(int *) &header[42];			/* Pixels per meter (unreliable) */
	infohd->ncolours = *(unsigned int *) &header[46];		/* Number of colours */
	infohd->importantcolours = *(unsigned int *) &header[50];	/* Important colours */
	return;
}

void printhd(bmpheader *hd) {
	printf("\nFile type: 0x%x", hd->type);
	printf("\nFile size: %u bytes", hd->size);
	printf("\nReserved: %hu\nReserved: %hu", hd->reserved1, hd->reserved2);
	printf("\nOffset to data: %u bytes", hd->offset);
	return;
}

void printinfohd(bmpinfoheader *infohd) {
	printf("\nHeader size: %u bytes", infohd->size);
	printf("\nWidth: %i pixels", infohd->width);
	printf("\nHeight: %i pixels", infohd->height);
	printf("\nPlanes: %hu", infohd->planes);
	printf("\nBit depth: %hu bits per pixel", infohd->bits);
	printf("\nCompression: %u (0 = none, 1 = RLE-8, 2 = RLE-4)", infohd->compression);
	printf("\nImage length: %u bytes", infohd->imagesize);
	printf("\nHorizontal resolution: %i pixels per meter", infohd->xresolution);
	printf("\nVertical resolution: %i pixels per meter", infohd->yresolution);
	printf("\nNumber of colours: %u", infohd->ncolours);
	printf("\nImportant colours: %u\n\n", infohd->importantcolours);
	return;
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

