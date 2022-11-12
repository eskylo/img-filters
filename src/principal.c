#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bmp.h"
#include "imgfilterproto.h"

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

	char fname[] = "./../lena_color.bmp";
	char out[] = "./../saida2.bmp";
	unsigned char *buf;
	int option, bsize, file_type;

	FILE *streamIn, *fo;

	unsigned int i;
	int sz;
	short threshold, bytes_pixel;

	char pgm_signature[10];
	char pgm_width[10];
	char pgm_height[10];
	char pgm_comments[100];
	char pgm_max[10];
	int width, height;

	streamIn = fopen(fname, "rb");	/* Open the file */
	if (streamIn == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < HDRBMP; i++) {
		header[i] = getc(streamIn);	/* Strip out BMP header, byte-wise */
	}

	file_type = 0;

	if (header[0] == 'P' && header[1] == '5') {
		printf("PGM P5 detected.\n");
		file_type = 2;
	}

	if (gethd(&header[0], &hd) == 0) {
		printf("BMP detected.\n");
	    file_type = 1;
	}

	if (file_type == 0) {
		fclose(streamIn);
	    perror("Invalid signature.\n");
	    exit(EXIT_FAILURE);
	}

	if (file_type == 1) {//BMP
		getinfohd(header, &infohd);

		if (infohd.bits <= HDRBD) {
			fread(colorTable, sizeof(unsigned char), HBMPCT, streamIn);
		}

		/* Avoid invalid requests */
		if (infohd.height < 0 || infohd.width < 0)
			perror("Overflow");

		/* Check for signed int overflow */
		if (infohd.height && infohd.width > INT_MAX / infohd.height)
			perror("Overflow");

		height = infohd.height;
		width = infohd.width;
		sz = height * width;
		bytes_pixel = infohd.bits/8;
	}
	
	if (file_type == 2) {//PGM
		rewind(streamIn);
		fscanf(streamIn, "%s\n", pgm_signature);
		printf("Signature[%s]\n", pgm_signature);
		fscanf(streamIn, "%[^\n]s", pgm_comments);
		printf("Comments(%s)\n", pgm_comments);
		fscanf(streamIn, "%s %s", pgm_width, pgm_height);
		printf("Dim{%s x %s}\n", pgm_width, pgm_height);
		fscanf(streamIn, "%s", pgm_max);
		printf("MAX{%s}\n", pgm_max);

		width = atoi(pgm_width);
		height = atoi(pgm_height);
		sz = height * width;
		bytes_pixel = 1;

		printf("Size{%d}\n", sz);
	}

	buf = (unsigned char *) malloc(sz*bytes_pixel);	/* To store the image data */

	if (buf == NULL) {
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	fread(buf, sizeof(unsigned char), sz*bytes_pixel, streamIn);

	do {

		/* Display menu */
		printf("Choose a filter:\n\n");
		printf("[0] Properties\n");
		printf("[1] White Border\n");
		printf("[2] Black Border\n");
		printf("[3] Negative\n");
		printf("[4] Gradient\n");
		printf("[5] Blur\n");
		printf("[6] Rotate\n");
		printf("[7] Blackwhite\n");
		printf("[8] Grayscale\n");
		printf("[9] Sepia\n");
		printf("[10] Exit\n");
		scanf("%d", &option);

		/* Properties */
		if (option == 0) {
			printf("\nBMP (Windows) header\n");
			printhd(&hd);
			printinfohd(&infohd);
			min_max_color(buf, width, height);
			real_size(&hd, &infohd);
		}

		/* Apply filter */
		if (option == 1) {/* White Border */
			printf("Enter the border size:\n\n");
			scanf("%d", &bsize);

			if (bsize > width || bsize > height)
				printf("Invalid border size.\n\n");
			else
				border(buf, width, height, bytes_pixel, 255, bsize);
		}

		if (option == 2) {/* Black Border */
			printf("Enter the border size:\n\n");
			scanf("%d", &bsize);

			if (bsize > width || bsize > height)
				printf("Invalid border size.\n\n");
			else
				border(buf, width, height, bytes_pixel, 0, bsize);
		}

		if (option == 3) /* Negative */
			negative(buf, width, height, bytes_pixel);
		
		if (option == 4) /* Gradient */
			gradient(buf, width, height);

		if (option == 5) /* Blur */
			blur(buf, width, height);

		if (option == 6) /* Rotate */
			rotate(buf, width, height);

		if (option == 7) {/* Blackwhite */
			printf("Enter the threshold:\n\n");
			scanf("%d", &threshold);

			if (threshold > 255 || threshold < 0)
				printf("Invalid threshold.\n\n");
			else
				blackwhite(buf, width, height, threshold);
		}

		if (option == 8) /* Grayscale */
			grayscale(buf, width, height);

		if (option == 9) /* Sepia */
			sepia(buf, width, height);
	
	} while (option != 10);

	fo = fopen(out, "wb");	/* Open the file */
	if (fo == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	if (file_type == 1) {//BMP
		/* Write the image header to output file */
		fwrite(header, sizeof(unsigned char), HDRBMP, fo);

		if (infohd.bits <= 8) {
			fwrite(colorTable, sizeof(unsigned char), HBMPCT, fo);
		}
	}
	
	if (file_type == 2) {//PGM
		fprintf(fo, "%s\n", pgm_signature);
		fprintf(fo, "%s\n", pgm_comments);
		fprintf(fo, "%d %d\n", width, height);
		fprintf(fo, "%s\n", pgm_max);
	}

	fwrite(buf, sizeof(unsigned char), sz*bytes_pixel, fo);

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