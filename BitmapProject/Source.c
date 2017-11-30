#include <stdio.h>
#include <Windows.h>

BITMAPFILEHEADER bmpHead;
BITMAPINFOHEADER bmpInfo;
RGBTRIPLE rgb;

RGBTRIPLE Gray(BYTE avg) {
	RGBTRIPLE rgb;
	rgb.rgbtRed = avg;
	rgb.rgbtGreen = avg;
	rgb.rgbtBlue = avg;
	return rgb;
}

int main() {
	char *path = "file.bmp";
	char *newpath = "modified.bmp";
	//scanf(!), like n and s where len(s) = n
	FILE *original, *modified;

	original = fopen(path, "r+b");
	fread(&bmpHead, sizeof(bmpHead), 1, original);
	fread(&bmpInfo, sizeof(bmpInfo), 1, original);

	modified = fopen(newpath, "w+b");
	fwrite(&bmpHead, sizeof(bmpHead), 1, modified);
	fwrite(&bmpInfo, sizeof(bmpInfo), 1, modified);

	const int extra_alignment = bmpInfo.biWidth % 4; //this alignment is true only for 24-bits bitmap. sizeof(pixel's "string") must be multiple 4 bytes
	
	for (int i = 0; i < bmpInfo.biHeight; i++) {
		for (int j = 0; j < bmpInfo.biWidth; j++) {
			fread(&rgb, sizeof(rgb), 1, original);
			BYTE avg = (rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3;
			rgb = Gray(avg);
			fwrite(&rgb, sizeof(rgb), 1, modified);
		}
		fwrite(NULL, sizeof(rgb), extra_alignment, modified);
	}

	fclose(original);
	fclose(modified);

	return 0;
}