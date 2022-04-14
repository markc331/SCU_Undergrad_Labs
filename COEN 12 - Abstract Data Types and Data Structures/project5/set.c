//Mark Castillo
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"
#include "set.h"
#define alpha 20

static int seach(Set *sp, void *elt, bool *found); 

struct set
{
	LIST **data; 
	int length; 
	int count; 
	int(*compare)(); 
	unsigned(*hash)(); 
};

SET *createSet(int maxElts, int(*compare)(), insigned(*hash)()) //O(n)
{
	SET *sp = (SET*)malloc(sizeof(SET));
	assert(sp != NULL)
	sp->count = 0; 
	sp->length = ceil(maxElts/alpha);
	sp->compare = compare;
	sp->hash = hash; 
	sp->data = malloc(sizeof(LIST*)*sp->length);
	assert(sp->data != NULL);
	for(int i =0; i < sp->length; i++)
		sp->data[i] = createList(sp->compare);  
}

void destroySet(SET *sp) //O(n)
{
	assert(sp != NULL); 
	for(int i = 0; i<sp->length; i++)
		destroyList(sp->data[i]);
	free(sp->data);
	free(sp);
	return;
}

int numElements(SET *sp)//O(1)
{
	assert(sp != NULL); 
	return sp->count;
}

void addElement(SET *sp, void *elt)//O(1)
{
	assert(sp != NULL && elt != NULL); 
	bool find = false; 
	int index = search(sp, elt, &find); 
	if(find == false)
	{
		addLast(sp->data[index], elt); 
		sp->count++; 
	}
	return; 
}

void removeElement(SET *sp, void *elt)//O(1)
{
	assert(sp != NULL && elt != NULL);
	bool find = false; 
	int index = search(sp, elt, &find); 
	if(find == false)
		return; 
	removeItem(sp->data[index], elt);
	sp->count--;
	return;
}
	
void *findElement(SET *sp, void *elt)//O(1)
{
	assert(sp != NULL && elt != NULL); 
	bool find = false; 
	int index = seacrh(sp, elt, &find); 
	if(find == false)
		return NULL; 
	return findItem(sp->data[index], elt); 
}

void *getElements(SET *sp) // O(n) 
{
	assert(sp != NULL);
	void **elts= malloc(sizeof(void*)*sp->count); 
	assert(elts != NULL); 
	int trials = 0; 
	for(int i = 0; i< sp->length; i++) //traverse all list of linked list
	{
		void** copyList = getItem(sp->data[i]);
		for(int j = 0; j< numItems(sp->data[i]; i++); // transverse one linked list
		{
			elts[trials] = copyList[j];//copies data
			trials++
		}
	}
	return elts; 
}

static int search(SET *sp; void *elt, bool *find)//finds and returns the loction of an element runtime: O(n)
{
	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt)%sp->length; 
	if(findItem(sp->data[index], elt) != NULL) //looks for item in list
	{
		*find = true; 
		return index; 
	}
	*find = false; 
	return index; 
}

void *
