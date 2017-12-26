#include "Image.h"
#include <stdlib.h>

const double R1 = 0.2126, G1 = 0.7152, B1 = 0.0722;
const double R2 = 0.299, G2 = 0.587, B2 = 0.114;
const int _4BYTES = 32;
WORD BM = ('M' << 8) + ('B' << 0);

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
}

void shift(FILE *original, FILE **modified, int bit_shift) {
	BYTE byte;
	fseek(original, bit_shift, SEEK_SET);
	for (int k = 0; k < N; k++) {
		fpos_t  f1, f2;
		fgetpos(original, &f1);
		fgetpos(modified[k], &f2);
		while (f1 != f2) {
			fwrite(&byte, sizeof(byte), 1, modified[k]);
			fgetpos(modified[k], &f2);
		}
	}
}