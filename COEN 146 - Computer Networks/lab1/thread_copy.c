// Name : Mark Castillo
// Date : Jan 14,2022
// Title : Lab 1 Basic Linux and C programming skills
// Description : copies from source file to destination using threads

// COEN 146L : Lab 1 - template to use for creating multiple thread to make file transfers (step 4)

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

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
	fclose(src);// closes src file pointer
	fclose(dst);// closes dst file pointer
	free(buf);// frees memory used for buf
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function
	func_copy(params.src_filename, params.dst_filename);
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if (argc != 5) {  // check correct usage
		fprintf(stderr, "usage: %s <parameters>", argv[0]);
		exit(1);
	}// check correct usage of arguments in command line
	char* src_filename;
	char* dst_filename;
	char* src_filenames[2] = {argv[1], argv[2]}; // array of source files
	char* dst_filenames[2] = {argv[3], argv[4]}; // array of desintation files
	int num_threads = 2; // number of threads to create
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	for (i = 0; i < num_threads; i++) {
		// initialize thread parameters
		thread_params[i].thread_id = i;
		thread_params[i].src_filename = src_filenames[i];
		thread_params[i].dst_filename = dst_filenames[i];
		// create each copy thread
		// use pthread_create(.....);
		pthread_create(&threads[i], NULL, copy_thread, (void *)&thread_params[i]);
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
}