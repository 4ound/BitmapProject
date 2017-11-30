#include "Image.h"
#include <string.h>
#include <stdio.h>


BITMAPFILEHEADER bmpHead;
BITMAPINFOHEADER bmpInfo;
RGBTRIPLE rgb;

const size_t n = 3;

char *get_path() {
	char input[240];
	const char *default_path = "file.bmp";
	printf("Drop or input filename here. To use default file \"file.bmp\" in root folder just type 0.\n");
	scanf("%s", &input);
	if (strcmp(input, "0") == 0) {
		return default_path;
	}
	else {
		return input;
	}
}

int main() {
	char *path = get_path();
	char *newpath[3] = {"modified_var1.bmp", "modified_var2.bmp", "modified_var3.bmp" };

	FILE *original, *modified[3];

	original = fopen(path, "r+b");
	fread(&bmpHead, sizeof(bmpHead), 1, original);
	fread(&bmpInfo, sizeof(bmpInfo), 1, original);

	for (int i = 0; i < n; i++) {
		modified[i] = fopen(newpath[i], "w+b");
		fwrite(&bmpHead, sizeof(bmpHead), 1, modified[i]);
		fwrite(&bmpInfo, sizeof(bmpInfo), 1, modified[i]);
	}


	const int extra_alignment = bmpInfo.biWidth % 4; //this alignment is true only for 24-bits bitmap. sizeof(pixel's "string") must be multiple 4 bytes
	
	for (int i = 0; i < bmpInfo.biHeight; i++) {
		for (int j = 0; j < bmpInfo.biWidth; j++) {
			fread(&rgb, sizeof(rgb), 1, original);

			BYTE avg[3] = { (rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3,
				(rgb.rgbtRed * r1 + rgb.rgbtGreen * g1 + rgb.rgbtBlue * b1),
				(rgb.rgbtRed * r2 + rgb.rgbtGreen * g2 + rgb.rgbtBlue * b2) };

			RGBTRIPLE rgb[3] = { Gray(avg[0]), Gray(avg[1]), Gray(avg[2]) };

			for (int i = 0; i < n; i++) {
				fwrite(&rgb[i], sizeof(rgb[i]), 1, modified[i]);
			}
		}
		for (int i = 0; i < n; i++) {
			fwrite(NULL, sizeof(rgb), extra_alignment, modified);
		}
	}

	_fcloseall();
	return 0;
}