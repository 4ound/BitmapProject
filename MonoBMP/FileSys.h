#ifndef FileSys
#define FileSys
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



const char *GEN_FILE_NAME[3] = { "modified_var1.bmp", "modified_var2.bmp", "modified_var3.bmp" };
const char *ORIG_FILE_NAME = "default.bmp";
const char *INPUT_FLAG = "--input=";
const char *OUTPUT_FLAG = "--output=";
const int N = 3;

void get_path(int argc, char **s, char **origin, char **modified) {
	*origin = NULL;
	for (int i = 0; i < N; i++) modified[i] = NULL;

	for (int i = 1; i < argc; i++) {
		if (strlen(s[i]) >= strlen(INPUT_FLAG) && strncmp(s[i], INPUT_FLAG, strlen(INPUT_FLAG)) == 0) {
			*origin = (char *)malloc(sizeof(char) * (strlen(s[i]) - strlen(INPUT_FLAG) + 1));
			strcpy(*origin, s[i] + strlen(INPUT_FLAG));
		}
		else if (strlen(s[i]) >= strlen(OUTPUT_FLAG) && strncmp(s[i], OUTPUT_FLAG, strlen(OUTPUT_FLAG)) == 0) {
			for (int j = 0; j < N; j++) {
				modified[j] = (char *)malloc(sizeof(char) * (strlen(s[i]) - strlen(OUTPUT_FLAG) + strlen(GEN_FILE_NAME[j]) + 1));
				strcpy(modified[j], s[i] + strlen(OUTPUT_FLAG));
				strcat(modified[j], GEN_FILE_NAME[j]);
			}
		}
	}

	if (*origin == NULL) {
		*origin = (char *)malloc(sizeof(char) * (strlen(ORIG_FILE_NAME) + 1));
		strcpy(*origin, ORIG_FILE_NAME);
	}
	if (modified[0] == NULL) {
		for (int j = 0; j < N; j++) {
			modified[j] = (char *)malloc(sizeof(char) * (strlen(GEN_FILE_NAME[j]) + 1));
			strcpy(modified[j], GEN_FILE_NAME[j]);
		}
	}
}

int _is_not_opened(FILE *file) {
	return file == NULL ? 1 : 0;
}

void _is_folder_correct(char **origin, char **modified) {
	printf("%s\n", *origin);
	for (int i = 0; i < N; i++) printf("%s\n", modified[i]);
}
#endif