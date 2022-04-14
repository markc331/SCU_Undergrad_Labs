#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
	int pageno;
	int bit;
} ref_page;


int indexOfItem(int page_num, ref_page cache[], int cacheSize) 
{
	int i;
    for( i = 0; i < cacheSize; i++) 
    {
        if(cache[i].pageno == page_num)
            return i;
    }
    return -1;
}

int switchBit(int x) 
{
    if(x == 1)
        return 0;
    else
        return 1;
}

int incrementPlace(int index, int cacheSize) 
{
    if(index + 1 == cacheSize)
        return 0;
    else 
        return index + 1;
}


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); 
    ref_page cache[C_SIZE]; 
    char pageCache[100];
    int placeInArray = 0;


    int i;
    int totalRequests = -1;
    int totalFaults = -1;
    
    for (i = 0; i < C_SIZE; i++)
    {
         cache[i].pageno = -1;
         cache[i].bit = -1;
    }

    while (fgets(pageCache, 100, stdin))
    {
    	int page_num = atoi(pageCache); 
        int x = indexOfItem(page_num, cache, C_SIZE);

        if(x == -1) 
        { 
            int i = placeInArray;
            bool found = false;
            do 
            {
                if(cache[i].bit <= 0) 
                {
                    found = true;
                    break;
                }
                else
                    cache[i].bit = switchBit(cache[i].bit);

                i = incrementPlace(i, C_SIZE);
            } while (i != placeInArray);
            if(found == false)
                i = C_SIZE - 1;

            cache[i].pageno = page_num;
            cache[i].bit = 0;
            totalFaults++;
            placeInArray = incrementPlace(i, C_SIZE);
        }
        else 
        { 
            cache[x].bit = switchBit(cache[x].bit);
        }
        totalRequests++;
    }
    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", totalRequests);
    double numMisses = totalFaults;
    double numRequests = totalRequests;
    double missRate = numMisses / numRequests;
    double hitRate = 1 - missRate;
    printf("Hit Rate = %f\n", hitRate);
    printf("\n");
    return totalFaults;
}
