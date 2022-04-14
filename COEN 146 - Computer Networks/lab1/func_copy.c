// Name : Mark Castillo
// Date : Jan 14,2022
// Title : Lab 1 Basic Linux and C programming skills
// Description : copies from source file to destination using functions

// COEN 146L : Lab 1 - template to use for file transfer (steps 1, 2, and 3)
// You need to adapt this template according to the requirements of each of the steps

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()
#include <sys/mman.h> // mmap()

#define BUF_SIZE 2048 //buffer size

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	
	FILE *src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	FILE *dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	char *buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data
	int m;
	while((m = fread(buf, 1, BUF_SIZE, src)) >0){
		fwrite(buf, 1, m, dst);
	}
	fclose(src); // closes src file pointer
	fclose(dst);// closes dst file pointer
	free(buf); // frees memory used for buf
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}
	func_copy(argv[1], argv[2]);
	return 0;
}