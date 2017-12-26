#ifndef FileSys
#define FileSys
#include <stdio.h>


extern const int N;

void get_path(int, char **, char **, char **);
int _is_not_opened(FILE *);
void _is_folder_correct(char **, char **);

#endif