#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int arg, char *argv[])
{
	pid_t pid; 
	int i, n = atoi(argv[i]);
	printf("\n Before forking \n");
	pid = fork();
	if(pid == -1) 
		fprintf(stderr, "can't fork, error %d\n", errno); 
	if(pid) //parent 
	{
		for(i = 0; i<100; i++)
		{
			printf("\t \t \t Parent Process %d \n", i);
			usleep(n);
		}
	}
	else //child 
	{
		for(i = 0; i<100; i++)
		{
			printf("Child Process %d \n",i); 
			usleep(n);
		}
	}
	return 0;
}
