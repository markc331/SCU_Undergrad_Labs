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
}; //creates a set with the specified integers and string 

SET *createSet(int maxElts)
{
	SET *p = (SET*)malloc(sizeof(SET)); //creates memory with the contents of the structure
	assert(p != NULL); //checks if there is anything in the memory 
	p->length = maxElts; //makes the length equal to the maxElts 
	p->count = 0;
	p->data = (char**)malloc(sizeof(char*)*maxElts); //creates new memory for the string 
	assert(p->data != NULL); //makes sure it isnt empty 
	return p;
} 

void destroySet(SET *p)
{
	assert(p != NULL); //checks if there is something to delete 
	free(p->data); //clears the string 
	free(p);  //clears the whole structure 
}

int numElements(SET *p)
{
	assert(p != NULL); 
	return p->count; //returns the number of elements 
}

void addElement(SET *p, char *elt)
{
	assert(p != NULL && elt != NULL); //checks if there is anything in the structure and if the character isnt empty 
	int index = search(p, elt, 0); //looks for the character 
	if(index < 0) 
	{
		p->data[p->count] = strdup(elt); //creates memory and stores the string into the position  
		p->count++; // increases the number of elements 
	}	
}

void removeElement(SET *p , char *elt) 
{
	assert(p!= NULL && elt != NULL); 
	int index = search(p, elt, 0); //search for the element 
	if(index <0)
		return; 
	for(int i = index; i< p->count; i++)
		p->data[i] = p->data[i+1]; // moves everyting to the left 
	p->count--; //decreases number of elements 
}

char *findElement(SET *p, char *elt)
{
	assert(p!= NULL && elt != NULL);
	int index =  search(p, elt, 0); // looks for the element 
	if(index < 0)
		return NULL; //if the element is not found
	else 
		return p->data[index];  // retruns the element
}

char **getElements(SET *p)
{
	assert(p!= NULL); 
	char** elements = (char**)malloc(sizeof(char*)*p->count);  
	elements = p->data; // copies the string into element
	return elements; 
}

static int search(SET *p, char *elt, bool* find)
{
	assert(p != NULL && elt != NULL);
	int index, found = -1; 
	for(int i= 0; i <p->count; i++)
	{
		if(strcmp(p->data[i], elt) == 0) //if they match 
		{
			found = 1;
			index = i; 
			break; 
		}
	}
	if(found ==1)
		return index; // returns the location 
	else 
		return -1; 

}
