#include <stdio.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
	FILE *fp; 				//file pointer created  
	int counter = 0;			//counter to keep track of how many words there are
	char n[MAX_WORD_LENGTH]; 		//characte string buffer
	fp = fopen(argv[1], "r");		// opens text file for reading 
	while((fscanf(fp, "%s", n)) == 1)	// make sure there is at least one word or string 
	{
		counter++;			//if there is a word or string there, this adds one to counter 
 	} 
	printf("%d\n", counter); 		//prints the total number of words in a file
}
