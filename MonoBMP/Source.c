#include "FileSys.h"
#include "Image.h"
#include "ErrorList.h"

BITMAPFILEHEADER bmpHead;
BITMAPINFOHEADER bmpInfo;
RGBQUAD rgbq;
RGBTRIPLE rgb;
BYTE byte;

int main(int argc, char **argv) {
	//char *s[] = { "--input=monobmp.bmp", "--output=C:Users:wtf" };
	char *original_path, *modified_path[3];
	if (argc > 3) ___error(1);
	get_path(argc, argv, &original_path, modified_path);

	FILE *original, *modified[3];
	original = fopen(original_path, "r+b");
	for (int i = 0; i < N; i++) modified[i] = fopen(modified_path[i], "w+b");

	/*free block*/
	_is_folder_correct(&original_path, modified_path);
	free(original_path);
	for (int i = 0; i < N; i++) free(modified_path[i]);
	/*end free block*/
	if (_is_not_opened(original)) ___error(2);
	for (int i = 0; i < N; i++) if (_is_not_opened(modified[i])) ___error(3);

	fread(&bmpHead, sizeof(bmpHead), 1, original);
	
	if (bmpHead.bfType != BM) ___error(0);
	fread(&bmpInfo, sizeof(bmpInfo), 1, original);

	for (int i = 0; i < N; i++) {
		fwrite(&bmpHead, sizeof(bmpHead), 1, modified[i]);
		fwrite(&bmpInfo, sizeof(bmpInfo), 1, modified[i]);
	}

	switch (bmpInfo.biBitCount) {
		case 32: {
			for (int i = 0; i < bmpInfo.biHeight; i++) {
				for (int j = 0; j < bmpInfo.biWidth; j++) {
					fread(&rgbq, sizeof(rgbq), 1, original);

					BYTE avg[3] = { (rgbq.rgbRed + rgbq.rgbGreen + rgbq.rgbBlue) / 3,
						(rgbq.rgbRed * r1 + rgbq.rgbGreen * g1 + rgbq.rgbBlue * b1),
						(rgbq.rgbRed * r2 + rgbq.rgbGreen * g2 + rgbq.rgbBlue * b2) };

					RGBQUAD argbq[3] = { GrayQ(avg[0]), GrayQ(avg[1]), GrayQ(avg[2]) };

					for (int k = 0; k < N; k++) fwrite(&argbq[k], sizeof(argbq[k]), 1, modified[k]);
				}
			}
			break;
		}
		case 24: {
			int padding = bmpInfo.biWidth % 4;
			for (int i = 0; i < bmpInfo.biHeight; i++) {
				for (int j = 0; j < bmpInfo.biWidth; j++) {
					fread(&rgb, sizeof(rgb), 1, original);

					BYTE avg[3] = { (rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3,
						(rgb.rgbtRed * r1 + rgb.rgbtGreen * g1 + rgb.rgbtBlue * b1),
						(rgb.rgbtRed * r2 + rgb.rgbtGreen * g2 + rgb.rgbtBlue * b2) };

					RGBTRIPLE argb[3] = { Gray(avg[0]), Gray(avg[1]), Gray(avg[2]) };

					for (int k = 0; k < N; k++) fwrite(&argb[k], sizeof(argb[k]), 1, modified[k]);
				}
				fread(&rgb, sizeof(rgb), padding, original);
				for (int k = 0; k < N; k++) fwrite(&rgb, sizeof(rgb), padding, modified[k]);
			}	
			break;
		}

		case 8:
		case 4:
		case 2:
		case 1: {
			int palette = (1 << bmpInfo.biBitCount);
			for (int i = 0; i < palette; i++) {
				fread(&rgbq, sizeof(rgbq), 1, original);
				BYTE avg[3] = { (rgbq.rgbRed + rgbq.rgbGreen + rgbq.rgbBlue) / 3,
					(rgbq.rgbRed * r1 + rgbq.rgbGreen * g1 + rgbq.rgbBlue * b1),
					(rgbq.rgbRed * r2 + rgbq.rgbGreen * g2 + rgbq.rgbBlue * b2) };
				RGBQUAD argbq[3] = { GrayQ(avg[0]), GrayQ(avg[1]), GrayQ(avg[2]) };
				for (int k = 0; k < N; k++) fwrite(&argbq[k], sizeof(argbq[k]), 1, modified[k]);
			}
			fseek(original, bmpHead.bfOffBits, SEEK_SET);
			for (int i = 0; i < bmpInfo.biHeight; i++) {
				for (int j = 0; j < amount_bytes(bmpInfo.biBitCount, bmpInfo.biWidth); j++) {
					fread(&byte, sizeof(byte), 1, original);
					for (int k = 0; k < N; k++) fwrite(&byte, sizeof(byte), 1, modified[k]);
				}
			}
			break;
		}
		default:
			___error(5);
	}


	/*fileclose block*/
	_fcloseall();
	/*fileclose block*/
	return 0;
}