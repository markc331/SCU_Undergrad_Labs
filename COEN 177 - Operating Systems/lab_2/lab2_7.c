#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int arg, char *argv[])
{
	pid_t child1, child2, child11, child12, child21, child22;

	child1 = fork(); //creates first child
	
	if(child1 == 0) 
	{
		child11 = fork(); //creates 2nd
		if(child11 == 0)
		{
			printf("I am child11 %d PID\n\n", getpid());
			exit(0);
		}		
		else
		{	
			child12 = fork(); 
			if(child12 == 0)
			{
				printf("I am child12 %d PID\n\n", getpid());
				exit(0);
			}
			else
			{
				printf("I am child1 %d PID\n\n", getpid());
				exit(0);
			}
		}
	}
	else
	{
		child2 = fork();
	
		if(child2 ==0)
		{
			child21 = fork(); 
			if(child21 == 0)
			{
				printf("I am child21 %d PID \n\n", getpid());
				exit(0);
			}
			else
			{
				child22 = fork();
				if(child22 ==0)
				{
					printf("I am child22 %d PID \n\n", getpid());
					exit(0);
				}
				else
				{
					printf("I am child2 %d PID \n\n", getpid());
					exit(0);
				}
			}
		}
		else
		{
			printf("I am Parent %d PID \n\n", getpid());
		}
	}
	return 0;
}
