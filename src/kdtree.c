/*
 * hw2.c
 *
 *  Created on: Feb 9, 2013
 *      Author: lou
 */
#include "kdtree.h"

/**
 * Computes the nth Fibonacci number
 * @see http://en.wikipedia.org/wiki/Fibonacci_number
 */
int fib(int n) {
	// TODO: compute the nth fibonacchi number
	if(n<1)return 0;
	if(n==1)return 1;
	int a = 1;
	int b = 0;
	int tmp = 0;
	while(n>0){
		tmp = b;
		b = a+b;
		a = tmp;
		n--;
	}
	return b;
}

/**
 * This function opens a directory and counts the number of files
 * in it.  If the path provided is not a directory or can
 * not be opened, this function returns 0.
 */
int numFiles(char* path) {
	DIR *dp; // a pointer to a directory
	int rv = 0; // the return value
	struct dirent *ep; // a directory entry

	// TODO: open the directory using opendir, and see if it was successful
	dp = opendir(path);
	if(dp != NULL){
		// TODO: Count the files in the directory
		while(readdir(dp))
			rv++;
		// TODO: close the directy
		closedir(dp);
	}
	// TODO: return result
	return rv;
}

/**
 * This function computes the size of a file (in bytes)
 * using the fopen and fseek commands.
 *
 * If the file can not be opened, return 0
 */
long int getFileSize(char* file) {
	FILE* f; // the file to open
	long int rv = 0; // the return value
	// TODO: See if you can open the file
	f = fopen(file, "r");
	if(f != NULL){
		// TODO: If successful, seek to the end of the file
		fseek(f,0,SEEK_END);
		// TODO: use ftell to see how far you seeked
		rv = ftell(f);
		// TODO: close the file
		fclose(f);
	}
	// TODO: return result
	return rv;
}

/**
 * This function looks up an evironment variable using the
 * getenv function.
 * @see http://www.cplusplus.com/reference/cstdlib/getenv/
 *
 * If the environment variable is not found,
 * you should return the string "None"
 */
char* getEnvValue(const char* name) {
	char * rv;

	// TODO: look up the environment variable
	rv = getenv(name);
	// TODO: check if it is  found
	if(rv == NULL)
		// TODO: if not, set the return value to "None"
		return "None";
	// TODO: return result
	return rv;
}