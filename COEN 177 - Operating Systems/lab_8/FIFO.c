#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	int pageno;
}ref_page;


int main(int argc, char *argv[])
{
	int C_SIZE = atoi(argv[1]);
	ref_page cache[C_SIZE];
	char pageCache[100];

	int i;
	int totalFaults = -1;
	int index = 0;
	int totalRequest = -1;

	for(i = 0; i< C_SIZE; i++)
	cache[i].pageno = -1;

	while(fgets(pageCache, 100, stdin))
	{
	int page_num = atoi(pageCache);

	for(i = 0; i < C_SIZE; i++)
	{
		if(cache[i].pageno == page_num)
			break;
		if(i == C_SIZE-1)
			{
				cache[index].pageno = page_num;
				totalFaults++;

				if(index + 1 == C_SIZE)
					index = 0;
				else
					index++;
			}

		}
		totalRequest++;
	}
	printf("numMiss: %d\n", totalFaults);
	printf("numRequest: %d\n", totalRequest);
	int hitNumber = totalRequest - totalFaults;
	float hitRate = hitNumber / ((double)totalRequest);
	printf("hit rate is: %5f\n", hitRate);
	printf("\n");
	return 0;
}
