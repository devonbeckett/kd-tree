#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>


int find(int n);

int numFiles(char* path);

long int getFileSize(char* file);

char* getEnvValue(const char* name);

