#define _BSD_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	
	pid_t pid;

	printf("\n Before forking \n");
	
	pid = fork();
	
	if(pid == -1)
		fprintf(stderr, "can't fork, error\n", errno);

	else if(pid == 0)
		execlp("/bin/ls", "ls", NULL);
	
	else
	{
		wait(NULL);
		printf("Child Complete");
		exit(0);
	}
	return 0;
}
