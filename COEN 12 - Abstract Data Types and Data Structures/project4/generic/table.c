//Mark Castillo
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#define empty 0 
#define filled 1
#define removed 2

static int search(SET *p, void* elt, bool* found);

struct set{

void** data;
char* flag;
int length; 
int count; 
int (*compare)(); 
unsigned (*hash)(); 
};

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	SET *p = (SET*)malloc(sizeof(SET));
	assert(p != NULL); 
	p->count = 0; 
	p->length = maxElts;
	p->compare = compare; 
	p->hash = hash; 
	p->data = malloc(sizeof(void*)*maxElts); 
	p->flag = (char*)malloc(sizeof(char)*maxElts); 
	assert(p->data != NULL && p->flag != NULL); 
	for(int i = 0; i<p->length; i++)
		p->flag[i] = empty; 
	return p; 
}
	
void destroySet(SET *p)
{
	assert(p != NULL); 
	for(int i = 0; i< p->count; i++)
	{
		if(p->data[i] == NULL)
			free(p->data[i]);
	}
	free(p->data); 
	free(p->flag); 
	free(p);
	return;
}

int numElements(SET *p)
{
	assert(p != NULL);
	return p->count;	
}

void addElement(SET *p, void *elt)
{
	assert(p != NULL && elt != NULL && p->count < p->length); 
	bool find = false;
	int index = search(p, elt, &find);
	if(find == false)
	{
		p->data[index] = elt;
		p->flag[index] = filled; 
		p->count++;
	}
	return;
}

void removeElement(SET *p, void *elt)
{
	assert(p != NULL && elt != NULL); 
	bool find = false; 
	int index = search(p, elt, &find);
	if(find == false)
		return; 
	p->flag[index] = removed; 
	p->count--; 
	return; 
}

void *findElement(SET *p, void *elt)
{
	assert(p !=  NULL && elt != NULL); 
	bool find = false; 
	int index = search(p, elt, &find);
	if(find == false)
		return NULL; 
	return p->data[index];
}

void *getElements(SET *p)
{
	assert(p != NULL);
	void** elts = malloc(sizeof(void*)*p->count); 
	assert(elts != NULL);
	int i, j;
	for(i = 0, j =0; i<p->length; i++)
	{
		if(p->flag[i] == filled)
			elts[j++] = p->data[i];
	}
	return elts; 
}

static int search(SET *p, void *elt, bool* find)
{
	assert(p != NULL && elt != NULL);
	int index = (*p->hash)(elt) % p->length; 
	int trials = 0; 
	int delSlot = -1; 
	while(trials < p->length) 
	{
		if(p->flag[index] == empty)
		{
			*find = false; 
			return delSlot != -1 ? delSlot : index; 
		}
		else if(p->flag[index] == removed)
		{
			trials++; 
			if(delSlot == -1)
				delSlot = index;
			index =(index + 1) % p->length; 
		}
		else
		{
			if((*p->compare)(p->data[index], elt) == 0)
			{
				*find = true; 
				return index;
			}
			else
			{
				index = (index +1) % p->length; 
				trials++;
			}
		}
	}
	*find = false; 
	return delSlot; 
}

