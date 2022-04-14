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
unsigned(*hash)(); 
};//created set with these in them

SET *createSet(int maxElts)
{
	SET *p = (SET*)malloc(sizeof(SET));//allocates memory 
	assert(p != NULL); 
	p->count = 0; 
	p->length = maxElts;
	p->data = malloc(sizeof(void*)*maxElts); //allocates memory for word
	p->flag = (char*)malloc(sizeof(char)*maxElts); //allocates for array of flags
	assert(p->data != NULL && p->flag != NULL); 
	for(int i = 0; i<p->length; i++)
		p->flag[i] = empty; //makes every flag empty
	return p; 
}
	
void destroySet(SET *p)
{
	assert(p != NULL); 
	for(int i = 0; i< p->count; i++)
	{
		if(p->data[i] == NULL) 
			free(p->data[i]); //frees every space
	}
	free(p->data); //frees word
	free(p->flag); //frees the corresponding flag
	free(p);//free set
	return;
}

int numElements(SET *p)
{
	assert(p != NULL);
	return p->count; //number of words	
}

void addElement(SET *p, char *elt)
{
	assert(p != NULL && elt != NULL && p->count < p->length); //checks if set, elt are empty and of count is less than length 
	bool find = false;
	int index = search(p, elt, &find); // looks for word 
	if(find == false)
	{
		p->data[index] = elt; //places it 
		p->flag[index] = filled; // changes corresponding flag to filled 
		p->count++; //increases number of words
	}
	return;
}

void removeElement(SET *p, char *elt) 
{
	assert(p != NULL && elt != NULL); 
	bool find = false; 
	int index = search(p, elt, &find);
	if(find == false) //if it isnt found
		return; 
	p->flag[index] = removed; // changes corresoponding flag 
	p->count--; // subtracts number of words
	return; 
}

char *findElement(SET *p, char *elt)
{
	assert(p !=  NULL && elt != NULL); 
	bool find = false; 
	int index = search(p, elt, &find);
	if(find == false) //if word isnt found 
		return NULL; 
	return p->data[index];//returns the index of the word 
}

char **getElements(SET *p)
{
	assert(p != NULL);
	void** elts = malloc(sizeof(void*)*p->count);  // allocates memory to copy 
	assert(elts != NULL);
	int i, j;
	for(i = 0, j =0; i<p->length; i++)
	{
		if(p->flag[i] == filled)
			elts[j++] = p->data[i];// copies word
	}
	return p->data[i]; //returns the place 
}

static int search(SET *p, void *elt, bool* find)
{
	assert(p != NULL && elt != NULL);
	int index = (*p->hash)(elt) % p->length; // looks for the slot  
	int trials = 0; 
	int delSlot = -1; 
	while(trials < p->length)
	{
		if(p->flag[index] == empty) //if nothing is in the slot 
		{
			*find = false;
			return delSlot != -1 ? delSlot : index; 
		}
		else if(p->flag[index] == removed)
		{
			trials++; //increases trials
			if(delSlot == -1)
				delSlot = index; //maxes it the index
			index =(index + 1) % p->length; //performs a hash 
		}
		else
		{
			if(strcmp(p->data[index], elt) == 0)
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

