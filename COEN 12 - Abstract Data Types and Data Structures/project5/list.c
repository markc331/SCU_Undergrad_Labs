//Mark Castillo

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef struct node
{
	void *data; 
	struct node *next; 
	struct node *prev; 
	
}NODE;

typedef struct list
{
	int count; 
	int (*compare)();
	NODE *head;
}LIST;

LIST *createList(int (*compare)())
{
	struct list *lp;
	lp = malloc(sizeof(struct list)); 
	assert(lp != NULL);
	lp->count = 0; 
	lp->compare = compare; 
	lp->head = malloc(sizeof(struct node)); 
	assert(lp->head != NULL); 
	lp->head->next = lp->head; 
	lp->head->prev = lp->head;  
	return lp;
}

void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *Cur;
	NODE *Prev = lp->head->prev;
	while(lp->count != 0)
	{
		Cur = Prev;
		Prev = Cur->prev; 
		free(Cur); 
		lp->count--;
	}
	free(lp);
}

int numItems(LIST *lp)
{
	assert(lp != NULL); 
	return lp->count; 
}

void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(struct node));
	assert(temp != NULL);
	temp->data = item; 
	temp->next = lp->head->next; 
	temp->prev = lp->head;
	lp->head->next->prev = temp;; 
	lp->head->next = temp;
	lp->count++;
	return;    	
}

void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(struct node));
	assert(temp != NULL);
	temp->data = item; 
	temp->next = lp->head; 
	temp->prev = lp->head->prev; 
	lp->head->prev->next = temp; 
	lp->head->prev = temp; 
	lp->count++;
	return;  
}

void *removeFirst(LIST *lp)
{
	assert(lp != NULL && lp->count >0);
	NODE *Cur = lp->head->next;
	void* copy = Cur->data;
	lp->head->next = Cur->next;
	Cur->next->prev = lp->head; 
	free(Cur); 
	lp->count--;
	return copy; 
}

void *removeLast(LIST *lp)
{
	assert(lp != NULL && lp->count >0);
	NODE *Cur = lp->head->prev;
	void *copy = Cur->data; 
	lp->head->prev = Cur->prev;
	Cur->prev->next = lp->head; 
	free(Cur);
	lp->count--;
	return copy; 
}

void *getFirst(LIST *lp)
{
	assert(lp != NULL && lp->count != 0); 
	return lp->head->next->data; 
}

void *getLast(LIST *lp)
{
	assert(lp != NULL && lp->count != 0); 
	return lp->head->prev->data; 
}

void removeItem(LIST *lp, void *item)
{
	assert(lp != NULL);
	if(lp->count >0)
	{
		NODE *Cur = lp->head->next;
		while(Cur != lp->head)
		{
			if((*lp->compare)(Cur->data, item) == 0)
			{
				Cur->prev->next = Cur->next;
				Cur->next->prev = Cur->prev; 
				free(Cur); 
				lp->count--;
				return;
			}
			Cur = Cur->next; 
		}
	}
	return; 
	
}

void *findItem(LIST *lp, void *item)
{
	assert(lp != NULL); 
	if(lp->count >0)
	{
		NODE *Cur = lp->head->next;
		while(Cur != lp->head)
		{
			if((*lp->compare)(Cur->data, item) == 0)
			{
				return Cur; 
			}
			Cur = Cur->next; 
		}
	}
	return NULL;
}

void *getItems(LIST *lp)
{
	assert(lp != NULL);
	NODE *Cur = lp->head->next; 
	void** item = malloc(sizeof(void*)*lp->count);
	assert(item != NULL); 
	int i = 0;
	while(Cur != lp->head)
	{
		item[i++] = Cur->data; 
		Cur = Cur->next;
	} 
	return item;
}
