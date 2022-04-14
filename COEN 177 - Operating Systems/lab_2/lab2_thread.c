#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


void *func1(int *n);
void *func2(int *n);

int main(int argc, char *argv[])
{
	pthread_t ptid1, ptid2;
	int i;
	int n = atoi(argv[1]);

	pthread_create(&ptid1, NULL, (void *)func1, &n);
	pthread_create(&ptid2, NULL, (void *)func2, &n);
	
	pthread_join(ptid1, NULL);
	pthread_join(ptid2, NULL);
	
	pthread_exit(NULL);
	
	return 0;
}

void *func1(int *n)
{
	int i; 
	for(i = 0; i< 100; i++)
	{
		printf("\t\t thread %d\n", i);
		usleep(*n);
	}
	return NULL;
}

void *func2(int *n)
{
	int i;
	for(i = 0; i<100; i++)
	{
		printf("\t thread %d \n", i);
		usleep(*n);
	}
	return NULL;
}
