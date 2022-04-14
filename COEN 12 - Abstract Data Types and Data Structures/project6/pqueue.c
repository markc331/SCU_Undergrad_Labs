//Mark Castillo

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

struct pqueue
{
	int count; 
	int length; 
	void **data; 
	int (*compare)(); 
};

PQ *createQueue(int (*compare)()) //creates the queue O(1)
{
	PQ *pq = malloc(sizeof(PQ)); 
	pq->compare = compare; 
	pq->count = 0; //empty array 
	pq->length = 10; 
	pq->data = malloc(sizeof(void*)*10); 
	assert(pq->data != NULL); 
	return pq; 
}

void destroyQueue(PQ *pq) //O(n) runtime to destroy the que 
{
	assert(pq != NULL); 
	free(pq->data); 
	free(pq);
	return; 
}

int numEntries(PQ *pq) // O(1) returns pq->count since that keeps track of elements withine the array 
{
	assert(pq != NULL); 
	return pq->count; 
}

void addEntry(PQ *pq, void *entry) // O(logn) 
{
	assert(pq != NULL); 
	if(pq->count == pq->length)
	{
		pq->length *= 2; 
		pq->data = realloc(pq->data, sizeof(void*)*pq->length); //doubles the array size 
		
	}
	pq->data[pq->count] = entry; 
	int index = pq->count; 
	while(pq->count != 0 && (*pq->compare)(pq->data[(index -1)/2], pq->data[index]) >0) //swaps if the child is smaller than the parent 
	{
		void *swapData = pq->data[index];
		pq->data[index] = pq->data[(index -1)/2];
		pq->data[(index -1)/2]= swapData; 
		index = ((index -1)/2); 
	}
	pq->count++;
	return;
}

void *removeEntry(PQ *pq) //O(logn)
{
	assert(pq != NULL);
	void *returnData = pq->data[0];
	pq->data[0] = pq->data[pq->count - 1];//swaps the root
	int index = 0; 
	while((index*2)+1 <= pq->count-1 ) //untilthere is not left child
	{
		int childIndex = ((index*2)+1);//gets index of left child
		if((index*2)+2 <= pq->count-1) 
		{
			if((*pq->compare)(pq->data[((index*2)+2)], pq->data[((index*2)+1)]) <0)
				childIndex = ((index*2)+2);
		}
			if((pq->compare)(pq->data[index],pq->data[childIndex]) <0)
				break; 
			else
			{
				void *swapData = pq->data[index];
				pq->data[index] = pq->data[childIndex];
				pq->data[childIndex] = swapData; 
			}
		
		index = childIndex; //checks child 
	}
	pq->count--; //return 
	return returnData; 
}
