#include <stdio.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
	FILE *fp; 
	int counter = 0;
	char n[MAX_WORD_LENGTH]; 
	fp = fopen(argv[1], "r");
	while((fscanf(fp, "%s", n)) == 1)
	{
		counter++;
 	} 
	printf("%d\n", counter); 
}
