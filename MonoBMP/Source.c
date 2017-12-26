#include "FileSys.h"
#include "Image.h"
#include "ErrorList.h"
#include <stdio.h>

BITMAPFILEHEADER bmpHead;
BITMAPINFOHEADER bmpInfo;
RGBQUAD rgbq;
RGBTRIPLE rgb;
BYTE byte;

int main(int argc, char **argv) {
	char *original_path, *modified_path[3];
	if (argc > 3) ___error(1);
	get_path(argc, argv, &original_path, modified_path);
	_is_folder_correct(&original_path, modified_path);
	FILE *original, *modified[3];

	/*free block*/
	original = fopen(original_path, "r+b");
	free(original_path);
	if (_is_not_opened(original)) ___error(2);

	for (int i = 0; i < N; i++) modified[i] = fopen(modified_path[i], "w+b");
	for (int i = 0; i < N; i++) free(modified_path[i]);
	for (int i = 0; i < N; i++) if (_is_not_opened(modified[i])) ___error(3);
	/*end free block*/

	fread(&bmpHead, sizeof(bmpHead), 1, original);
	
	if (bmpHead.bfType != BM) ___error(0);
	fread(&bmpInfo, sizeof(bmpInfo), 1, original);

	for (int i = 0; i < N; i++) {
		fwrite(&bmpHead, sizeof(bmpHead), 1, modified[i]);
		fwrite(&bmpInfo, sizeof(bmpInfo), 1, modified[i]);
	}

	switch (bmpInfo.biBitCount) {
		case 32: {
			shift(original, modified, bmpHead.bfOffBits);
			for (int i = 0; i < bmpInfo.biHeight; i++) {
				for (int j = 0; j < bmpInfo.biWidth; j++) {
					fread(&rgbq, sizeof(rgbq), 1, original);

					BYTE avg[3] = { (rgbq.rgbRed + rgbq.rgbGreen + rgbq.rgbBlue) / 3,
						(rgbq.rgbRed * R1 + rgbq.rgbGreen * G1 + rgbq.rgbBlue * B1),
						(rgbq.rgbRed * R2 + rgbq.rgbGreen * G2 + rgbq.rgbBlue * B2) };

					RGBQUAD argbq[3] = { GrayQ(avg[0]), GrayQ(avg[1]), GrayQ(avg[2]) };

					for (int k = 0; k < N; k++) fwrite(&argbq[k], sizeof(argbq[k]), 1, modified[k]);
				}
			}
			break;
		}
		case 24: {
			
			
			shift(original, modified, bmpHead.bfOffBits);
			int padding = bmpInfo.biWidth % 4;
			for (int i = 0; i < bmpInfo.biHeight; i++) {
				for (int j = 0; j < bmpInfo.biWidth; j++) {
					fread(&rgb, sizeof(rgb), 1, original);

					BYTE avg[3] = { (rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3,
						(rgb.rgbtRed * R1 + rgb.rgbtGreen * G1 + rgb.rgbtBlue * B1),
						(rgb.rgbtRed * R2 + rgb.rgbtGreen * G2 + rgb.rgbtBlue * B2) };

					RGBTRIPLE argb[3] = { Gray(avg[0]), Gray(avg[1]), Gray(avg[2]) };

					for (int k = 0; k < N; k++) fwrite(&argb[k], sizeof(argb[k]), 1, modified[k]);
				}
				fread(&rgb, sizeof(rgb), padding, original);
				for (int k = 0; k < N; k++) fwrite(&rgb, sizeof(rgb), padding, modified[k]);
			}	
			break;
		}
		case 16: {
			break;
		}
		case 8:
		case 4:
		case 2:
		case 1: {
			//int palette = (1 << bmpInfo.biBitCount);
			int palette = bmpInfo.biClrUsed;

			shift(original, modified, sizeof(bmpHead) + bmpInfo.biSize);

			for (int i = 0; i < palette; i++) {
				fread(&rgbq, sizeof(rgbq), 1, original);
				BYTE avg[3] = { (rgbq.rgbRed + rgbq.rgbGreen + rgbq.rgbBlue) / 3,
					(rgbq.rgbRed * R1 + rgbq.rgbGreen * G1 + rgbq.rgbBlue * B1),
					(rgbq.rgbRed * R2 + rgbq.rgbGreen * G2 + rgbq.rgbBlue * B2) };
				RGBQUAD argbq[3] = { GrayQ(avg[0]), GrayQ(avg[1]), GrayQ(avg[2]) };
				for (int k = 0; k < N; k++) fwrite(&argbq[k], sizeof(argbq[k]), 1, modified[k]);
			}

			shift(original, modified, bmpHead.bfOffBits);

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