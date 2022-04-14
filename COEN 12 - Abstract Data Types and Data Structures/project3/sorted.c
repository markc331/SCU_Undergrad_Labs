#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

static int search(SET *p, char *elt, bool *found); 

struct set{
	char** data; 
	int length; 
	int count; 
}; //creates a structure with a string, and two integers 

SET *createSet(int maxElts)
{
	SET *p = (SET*)malloc(sizeof(SET)); //creates new memeory with the contents in the structure
	assert(p != NULL);  //checks if the newly allocated memory has anything in it
	p->length = maxElts; //sets the length to the max number of elements 
	p->count = 0;
	p->data = (char**)malloc(sizeof(char*)*maxElts); //creates a new string array
	assert(p->data != NULL); // checks if the string has anything 
	return p;
} 

void destroySet(SET *p)
{
	assert(p != NULL); //checks if it has anything in it
	free(p->data); //clears everything in the string array 
	free(p);  //clears the whole struct
}

int numElements(SET *p)
{
	assert(p != NULL); 
	return p->count; // gives the number of elements 
}

void addElement(SET *p, char *elt)
{
	assert(p != NULL && elt != NULL && p->count <= p->length); //makes sure that the struct and the character have something in them 
	bool find = false;
	int index = search(p, elt, &find); // looks for the character 
	if(find == false) 
	{
		for(int i = p->count; i >index; i--)
			p->data[i] = p->data[i-1]; //shifts everything to the left 
		p->data[index] = strdup(elt); // allocates memory for the character and it places the character there
		p->count++; //increases the number of elements 
	}	
}

void removeElement(SET *p , char *elt) 
{
	assert(p!= NULL && elt != NULL); 
	bool find = false; 
	int index = search(p, elt, &find); 
	if(find == false)
		return; 
	for(int i = index; i< p->count; i++)
		p->data[i] = p->data[i+1]; //moves everything to the left 
	p->count--; // decreases count since you are removing an element 
}

char *findElement(SET *p, char *elt)
{
	assert(p!= NULL && elt != NULL);
	bool find = false;
	int index =  search(p, elt, &find); 
	if(find == false)
		return NULL; // means that the element isnt found 
	else 
		return p->data[index];  // returns the element that was given 
}

char **getElements(SET *p)
{
	assert(p!= NULL); 
	char** elements = (char**)malloc(sizeof(char*)*p->count);  // allocates memory to store the string
	elements = p->data; // copies the string into element 
	return elements; // returns the string 
}

static int search(SET *p, char *elt, bool* find)
{
	assert(p != NULL && elt != NULL);
	int low, high, mid; 
	low = 0; 
	high = p->count-1; // makes high equal to the last string before '\0'
	while(low <= high)
	{
		mid = (low+high)/2; //splits the string in half 
		if(strcmp(p->data[mid], elt) <0)//focuses on the bottom half 
			high = mid-1; //makes the mid the new high 
		else if(strcmp(p->data[mid], elt) >0)//focuses on the top half 
			low= mid +1;// makes mid the new low
		else
		{
			*find = true; //if the mid is the actual character, then it found it
			return mid; 
		}
	}
	*find = false; //if the words isnt there 
	return low; 
}
