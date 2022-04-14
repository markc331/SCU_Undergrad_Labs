#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int arc, char *argv[])
{
	int fds[2];
	pipe(fds);

	if(fork() ==0)
	{
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("/bin/grep", "grep", "root", 0);
	}

	else if(fork() == 0 )
	{
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("/bin/cat", "cat", "/etc/passwd", 0);
	}
	
	else
	{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
}
