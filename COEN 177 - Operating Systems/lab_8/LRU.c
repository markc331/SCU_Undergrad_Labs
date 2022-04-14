#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
	int pageno;
	int index;
}ref_page;


int main(int argc, char *argv[])
{
	int C_SIZE = atoi(argv[1]);
	ref_page cache[C_SIZE];
	char pageCache[100];

	int i, j, k, position;
	int totalFaults = -1; 
	int recent = -1;
	int totalRequest = -1;
	
	for (i = 0; i < C_SIZE; i++) 
	{ 
		cache[i].pageno = -1;
		cache[i].index = 100;
	}

	while (fgets (pageCache, 100, stdin))
	{
		int page_num = atoi (pageCache);
		totalRequest++;

	for (i = 0; i < C_SIZE; i++)
	{ 
            position = 0;
            recent = cache[i].index;
            if (page_num == cache[i].pageno)
            {
                for (j = 0; j < C_SIZE; j++)
                {
                    if (cache[j].index < cache[i].index)
                        cache[j].index++;
		        }
		        cache[i].index = 0;
                break;
            }
            if (i == C_SIZE - 1)
            { 
                for (k = 0; k < C_SIZE; k++)
                    cache[k].index++;
		        for (j = 0; j < C_SIZE; j++)
                {
                    if (recent < cache[j].index)
                    {
                        recent = cache[j].index;
                        position = j;
		            }
		        }
		
		        cache[position].pageno = page_num;
		        cache[position].index = 0;
		        totalFaults++;
            }
        }
    }
    printf("numMiss: %d\n", totalFaults);
    printf("numRequest: %d\n", totalRequest);
    int hitNumber = totalRequest - totalFaults;
    float hitRate = hitNumber / ((double)totalRequest);
    printf("hit rate is: %5f\n", hitRate);
    printf("\n");
    return 0;
}
