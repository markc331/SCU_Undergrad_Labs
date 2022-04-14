//Mark Castill
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE; 

static void readFile(char *filename); 
static NODE *mkNode(int data, NODE *left, NODE *right); 
static int depth(NODE *np); 
static int nodeCmp(NODE *np1, NODE *np2);

int ascii[257];//array for ascii characters
NODE *nodes[257]; // a priority queue

int main(int argc, char*argv[])
{
	if(argc ==2)
	{
		printf("Insufficient number of Files\n");
		return 0; 
	}
	else
	{
		readFile(argv[1]);
	}
	PQ *pq = createQueue(nodeCmp); //creates queue and sends it to the pqueue
	for(int i = 0; i<257; i++) //creates leafs and puts it into the queue 
	{
		if(ascii[i]>0)
		{
			nodes[i] = mkNode(ascii[i], NULL, NULL); 
			addEntry(pq, nodes[i]);
		}
	}
	nodes[256] = mkNode(0, NULL, NULL); //makes sure the queue isn't empty
	addEntry(pq, nodes[256]);
	while(numEntries(pq) >1)
	{
		NODE *left = removeEntry(pq); 
		NODE *right = removeEntry(pq);
		NODE *parent= mkNode(left->count +right->count, left, right); //smallest node is the root
		addEntry(pq, parent); 
	}
	for(int j = 0; j< 256; j++) //prints out the buts used for the char
	{
		if(nodes[j] != NULL)
		{
			printf(isprint(j) ? "%c" : "%03o",j);
			printf(": %d x %d bits = %d bits\n", ascii[j],depth(nodes[j]), ascii[j]*depth(nodes[j]));
		}
	}
	pack(argv[1], argv[2], nodes); 
	destroyQueue(pq);
	return 0; 
}

static void readFile(char *fileName) //open and reads the file 
{
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		puts("File Cannot be Opened");
		return; 
	}
	int x = getc(fp); 
	while(x != EOF)
	{
		ascii[x]++; 
		x = getc(fp);
	}
	fclose(fp); 
	return; 
}

static NODE *mkNode(int data, NODE *left, NODE *right) //organizes the nodes 
{
	NODE *root = malloc(sizeof(NODE));
	assert(root != NULL); 
	root->count = data; 
	root->parent = NULL; 
	if(left != NULL)
		left->parent = root;
	if(right != NULL)
		right->parent = root; 
	return root; 
}

static int depth(NODE *np) //returns the depth of a node
{
	assert(np != NULL); 
	if(np->parent == NULL)
		return 0; 
	return depth(np->parent) +1; 
}

static int nodeCmp(NODE *np1, NODE *np2) //returns the bigger node
{
	assert(np1 != NULL && np2 != NULL);
	return (np1->count < np2->count) ? -1 :(np1->count > np2->count); 
}
