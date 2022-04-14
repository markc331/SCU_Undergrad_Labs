//Mark Castillo

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

#define MAX 20


typedef struct list //makes a list of nodes
{
	struct node *head; //head and tail pointers make it easier for to remove the first and last item
	struct node *tail; 
	int countTot; //total number of items in the linked list
}LIST;

typedef struct node //makes a circular queue within each node
{
	void **data;
	int first;
	int length;	
	int count; //number of items in a cicular que
	struct node *next;
	struct node *prev;
}NODE;

NODE *newNode(int length); 

LIST *createList(void)
{
	LIST *lp = malloc(sizeof(LIST)); //creates a node list
	lp->head = lp->tail = newNode(MAX); 
	lp->countTot = 0; 
	return lp; 
}

NODE *newNode(int length) // makes creation of node easier for the list creation as well as for adding nodes to the list
{
	NODE *new = malloc(sizeof(NODE)); 
	assert(new != NULL);
	new->data = malloc(sizeof(void**)*length); // creates the circular queue
	new->count = 0; 
	new->first = 0; 
	new->length = length; 
	new->next = NULL; 
	new->prev = NULL; 
	return new;
}

void destroyList(LIST *lp)
{
	assert(lp != NULL); 
	NODE *p;
	while(lp->head != NULL) //forever loop that transverses the array
	{
		p = lp->head;
		lp->head = lp->head->next; // moves over head pointer one
		free(p->data); 
		free(p); 
	}
	free(lp);
	return;
}

int numItems(LIST *lp)
{
	assert(lp != NULL); 
	return lp->countTot; //total number of items in the list
}

void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	if(lp->head->count == lp->head->length) //if there is no space in the head node
	{
		NODE* temp = newNode(lp->head->length *2); //creates new node
		temp->next = lp->head; 
		lp->head = temp; 
		temp->next->prev = temp;
	}
	int index = (((lp->head->first + lp->head->length) - 1) % lp->head->length); // creates the index for the first term
	lp->head->data[index] = item; 
	lp->head->first = index; //makes the index of the item the new first 
	lp->head->count++; 
	lp->countTot++; 
	return; 
}

void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL); 
	if(lp->tail->count ==  lp->tail->length) //if there is no space in the tail node
	{	
		NODE *temp = newNode(lp->tail->length *2); 
		temp->prev = lp->tail; 
		lp->tail->next = temp;
		lp->tail = temp;	
	}
	int index = ((lp->tail->first + lp->tail->count) % lp->tail->length); //creates an index of the first item 
	lp->tail->data[index] = item;
	lp->tail->count++;
	lp->countTot++;
	return; 
}

void *removeFirst(LIST *lp)
{
	assert(lp != NULL); 
	if(lp->head->count == 0) //if circular list is empty then this deletes the head node
	{
		lp->head = lp->head->next; 
		free(lp->head->prev);  
		lp->head->prev = NULL; 
	} 	
	int index = lp->head->first; // removes the first index in the list
	int new = (index + 1) % lp->head->length; // moves the first over one position
	lp->head->first = new; 
	lp->head->count--; 
	lp->countTot--; 
	return lp->head->data[index]; //returns the removed item
}

void *removeLast(LIST *lp)
{
	assert(lp != NULL); 
	if(lp->tail->count == 0) //if circular list in tail is empty then it deletes it
	{
		NODE *p = lp->tail;
		lp->tail = lp->tail->prev;
		lp->tail->next = NULL; 
		free(p->data);
		free(p); 
	}	
	int index = (lp->tail->first + lp->tail->count) % lp->tail->length; // looks for the index of the last element in the list
	lp->tail->count--; 
	lp->countTot--; 
	return lp->tail->data[index]; // returns the last index
}

void *getItem(LIST *lp, int index)
{
	assert(lp != NULL && index >= 0 && index < lp->countTot); 
	NODE *p = lp->head;
	while(index >= p->count) // if the index is greater than the amount of elements,  then this subtracts it until it hits the right node
	{
		index -= p->count;
		p = p->next;
	}
	return p->data[(p->first + index) %p->length]; // position of the item and returns it
}


void setItem(LIST *lp, int index, void *item)
{
	assert(lp != NULL && index >= 0 && index < lp->head->count);
	NODE *p = lp->head;
	while( index >= p->count) // if the index is greater than the amount of elements, then this subtracts it until it hits the right node
	{
		index -= p->count; 
		p = p->next; 
	}
	p->data[(p->first + index) % p->length] = item; //sets the index of the element to the item
	return;
}
