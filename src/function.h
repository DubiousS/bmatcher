#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#define ALPHABET_LEN 256

#ifndef FUNCTION_H
#define FUNCTION_H
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void dirout(DIR *cdir, char *path);
void list_dir (const char * dir_name, const int f, char *pattern);
int file_read(const char * path, char * pattern);

#endif




