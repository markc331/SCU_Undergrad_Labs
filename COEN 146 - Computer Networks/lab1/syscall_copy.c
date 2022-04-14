// Name : Mark Castillo
// Date : Jan 14,2022
// Title : Lab 1 Basic Linux and C programming skills
// Description : copies from source file to destination using system calls

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
#include <sys/types.h>
#include <string.h>

#define BUF_SIZE 2048 //buffer size

// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char* src_filename, char* dst_filename)  {
	
	int src_fd = open(src_filename, O_RDONLY);	// opens a file for reading
	if (src_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		close(src_fd);
		exit(0);
	}
	// O_WRONLY - write only
	// O_CREAT - create file if it doesn't exist
	// O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
	// opens a file for writing; erases old file/creates a new file
	int dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC);	
	if (dst_fd < 0) { // open() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		close(dst_fd);
		exit(0);
	}


	// read/ write loop
	char* buf = malloc((size_t)BUF_SIZE);   // allocate a buffer to store read data
	int m;
	while((m = read(src_fd, buf, BUF_SIZE)) > 0) // reads up to BUF_SIZE bytes from src_filename
	{
		write(dst_fd, buf, m);// writes bytes_read to dst_filename
	}
	close(src_fd); // closes src_fd file descriptor
	close(dst_fd); // closes dst_fd file descriptor
	free(buf); // frees memory used for buf

	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {  // check correct usage
		fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
		exit(1);
	}
    
	syscall_copy(argv[1], argv[2]);
	
	return 0;
}