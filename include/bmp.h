
/*
  The bitmap file format:
  . Bitmap file header
  . Bitmap info header
  . Palette data (color table)
  . Bitmap data

  BMP (Windows) Header Format
  offset	size	description
  	0	2	signature, must be 4D42 hex
  	2	4	size of BMP file in bytes (unreliable)
  	6	2	reserved, must be zero
  	8	2	reserved, must be zero
  	10	4	offset to start of image data in bytes
  	14	4	size of BITMAPINFOHEADER structure, must be 40
  	18	4	image width in pixels
  	22	4	image height in pixels
  	26	2	number of planes in the image, must be 1
  	28	2	number of bits per pixel (1, 4, 8, or 24)
  	30	4	compression type (0=none, 1=RLE-8, 2=RLE-4)
  	34	4	size of image data in bytes (including padding)
  	38	4	horizontal resolution in pixels per meter (unreliable)
  	42	4	vertical resolution in pixels per meter (unreliable)
  	46	4	number of colors in image, or zero
  	50	4	number of important colors, or zero
*/

#define	HDRBMP 54
#define	HBMPCT 1024
#define	HDRBD  8

#pragma pack(push, 1)
typedef struct {
	unsigned short int type;	 /* Magic identifier            */
	unsigned int size;		 /* File size in bytes          */
	unsigned short int reserved1, reserved2;
	unsigned int offset;		 /* Offset to image data, bytes */
} bmpheader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	unsigned int size;               /* Header size in bytes        */
	int width, height;               /* Width and height of image   */
	unsigned short int planes;       /* Number of colour planes     */
	unsigned short int bits;         /* Bits per pixel              */
	unsigned int compression;        /* Compression type            */
	unsigned int imagesize;          /* Image size in bytes         */
	int xresolution, yresolution;    /* Pixels per meter            */
	unsigned int ncolours;           /* Number of colours           */
	unsigned int importantcolours;   /* Important colours           */
} bmpinfoheader;
#pragma pack(pop)
