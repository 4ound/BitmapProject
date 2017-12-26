#ifndef ErrorList
#define ErrorList
#include "ErrorList.h"

const char *BMP_ONLY = "Hey! This program support only Bitmap files\n";

const char *ARGUMENT_ERROR = "Supported flags\n" \
"--input=  Destination of original bmp\n" \
"--output= Path to modified bmp\n" \
"Missing flag mean that program replace it: --input=default.bmp and write modifications in current folder\n\n";

const char *FILE_READ_ERROR = "No such file in directory.\n" \
"Please, check filename and try again.\n\n";

const char *FILE_WRITE_ERROR = "Program can't get access to specified files or directory.\n" \
"Please be sure, that you've not typo errors and specified directory isn't reserved by the system.\n";

const char *BITS_ERROR = "Hmm... Something went wrong.\n" \
"Program couldn't transform that type of bmp.\n\n";

void ___error(int flag) {
	printf("Error code: %d\n", flag);
	switch (flag) {
		case 0:
			printf("%s\n", BMP_ONLY);
			break;
		case 1:
			printf("%s\n", ARGUMENT_ERROR);
			break;
		case 2:
			printf("%s\n", FILE_READ_ERROR);
			break;
		case 3:
			printf("%s\n", FILE_WRITE_ERROR);
			break;
		case 5:
			printf("%s\n", BITS_ERROR);
			break;
	}
	exit(flag);
}

#endif