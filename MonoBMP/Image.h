#ifndef Image
#define Image
#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

extern const double R1, G1, B1;
extern const double R2, G2, B2;
extern const int _4BYTES;
extern WORD BM;
extern const int N;

#pragma pack(push, 1)
typedef struct {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;

typedef struct {
	BYTE rgbtBlue;
	BYTE rgbtGreen;
	BYTE rgbtRed;
} RGBTRIPLE;

typedef struct {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)


RGBTRIPLE Gray(BYTE);
RGBQUAD GrayQ(BYTE);
int amount_bytes(int, int);
void shift(FILE *, FILE **, int);

#endif