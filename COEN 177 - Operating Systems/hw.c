#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *go(void *);
pthread_t threads;

int main()
{
	int i = 3;
	if(fork() == 0)
		pthread_create(&threads, NULL, go, &i);
	else if(fork() == 0)
		pthread_create(&threads, NULL, go &i);
	pthread_join(threads, NULL);
	return 0;
}

void *go(void *arg)
{
	printf("Hello from thread with value %d \n" , *(int *)arg);
	return 0;
}
