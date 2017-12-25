#ifndef Image
#define Image
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

const double r1 = 0.2126, g1 = 0.7152, b1 = 0.0722;
const double r2 = 0.299, g2 = 0.587, b2 = 0.114;
const int _4BYTES = 32;
WORD BM = 19778;


#pragma pack(push, 1)


typedef struct {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

typedef struct {
	BYTE rgbtBlue;
	BYTE rgbtGreen;
	BYTE rgbtRed;
} RGBTRIPLE;

typedef struct {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)


RGBTRIPLE Gray(BYTE avg) {
	RGBTRIPLE rgb;
	rgb.rgbtRed = avg;
	rgb.rgbtGreen = avg;
	rgb.rgbtBlue = avg;
	return rgb;
}

RGBQUAD GrayQ(BYTE avg) {
	RGBQUAD rgb;
	rgb.rgbRed = avg;
	rgb.rgbGreen = avg;
	rgb.rgbBlue = avg;
	rgb.rgbReserved = 0;
	return rgb;
}

int amount_bytes(int bit, int width) {
	return (bit * width + _4BYTES - 1) / _4BYTES * 4;
};

#endif


/*
typedef long            FXPT2DOT30;
typedef struct tagCIEXYZ {
FXPT2DOT30 ciexyzX;
FXPT2DOT30 ciexyzY;
FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
CIEXYZ  ciexyzRed;
CIEXYZ  ciexyzGreen;
CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;



typedef struct {
DWORD        bV4Size;
LONG         bV4Width;
LONG         bV4Height;
WORD         bV4Planes;
WORD         bV4BitCount;
DWORD        bV4V4Compression;
DWORD        bV4SizeImage;
LONG         bV4XPelsPerMeter;
LONG         bV4YPelsPerMeter;
DWORD        bV4ClrUsed;
DWORD        bV4ClrImportant;
DWORD        bV4RedMask;
DWORD        bV4GreenMask;
DWORD        bV4BlueMask;
DWORD        bV4AlphaMask;
DWORD        bV4CSType;
CIEXYZTRIPLE bV4Endpoints;
DWORD        bV4GammaRed;
DWORD        bV4GammaGreen;
DWORD        bV4GammaBlue;
} BITMAPV4HEADER;

typedef struct {
DWORD        bV5Size;
LONG         bV5Width;
LONG         bV5Height;
WORD         bV5Planes;
WORD         bV5BitCount;
DWORD        bV5Compression;
DWORD        bV5SizeImage;
LONG         bV5XPelsPerMeter;
LONG         bV5YPelsPerMeter;
DWORD        bV5ClrUsed;
DWORD        bV5ClrImportant;
DWORD        bV5RedMask;
DWORD        bV5GreenMask;
DWORD        bV5BlueMask;
DWORD        bV5AlphaMask;
DWORD        bV5CSType;
CIEXYZTRIPLE bV5Endpoints;
DWORD        bV5GammaRed;
DWORD        bV5GammaGreen;
DWORD        bV5GammaBlue;
DWORD        bV5Intent;
DWORD        bV5ProfileData;
DWORD        bV5ProfileSize;
DWORD        bV5Reserved;
} BITMAPV5HEADER;

*/