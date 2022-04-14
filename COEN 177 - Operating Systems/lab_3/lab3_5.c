#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int fds[2];
	char buffer[60];
	int count;
	int i;
	
	pipe(fds);
	memset(buffer, 0, sizeof(buffer));
	if(fork() == 0)
	{
		printf("\nWriter on the upstream end of them pipe -> %d arguments \n", argc);
		close(fds[0]);
		for(i = 1; i< argc; i++)
			strcat(buffer, argv[i]); // puts string into buffer
		write(fds[1], buffer, strlen(buffer)); //writes into fds[1]
		exit(0);
	}
	
	else if(fork() == 0)
	{
		printf("\nReader on the downstream end of the pipe \n");
		close(fds[1]);

		read(fds[0], buffer, 60); //reads into fds[0]
		printf("\n");

		write(1, buffer, 60); //writes from buffer
		printf("\n");

		exit(0);
	}

	else
	{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
