#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 20
#define ENTRY struct entry

void Insert(void);
void Delete(void); 
void List(void);
void fit_in(void); 
int duplicate(char *);

struct entry
	{    
		char name[LENGTH];
		int size;
		ENTRY *next; 
	}; 

ENTRY *head = NULL; 
ENTRY *tail = NULL; 

int main()
	{
		int option = 1;


 
		while(option != 0)		// creates forever loop 
			{
				printf("\nResturaunt Waiting List\n	Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 0 - Exit\nEnter Option: "); 
				scanf("%d" ,  &option);	//user inputs option 
				printf("\n");
					
				switch(option)
					{
						case 1:
							Insert(); 	//refers to insert function 
							break;
						case 2: 
							Delete();	// refers to delete function 
							break;
			
						case 3: 
							List();		//refers to list function 
							break;

						case 4: 
							fit_in(); 
							break;
						case 0: 
							return 0; 
						default:
							printf("Invalid Input"); 
					} 
			}

	
	}	
	

void Insert(void)
	{
		ENTRY *temp; 
		char n[LENGTH];
		int s;
 
		printf("Enter Name: "); 
		scanf ("%s", n);	  //user enters name and stores it in the current element 
			 
		if(duplicate(n)==1)  //goes to the duplicate function to look for duplicate names 
			return;
	
 		printf("Enter Party Size: ");
		scanf("%d", &s);

		temp = (ENTRY *)malloc(sizeof(ENTRY));
 
		strcpy(temp->name, n); 
		temp->size = s;
		temp->next = NULL; 
		if(head == NULL)
			head = tail = temp;  // since no memory is allocated in temp, the temp is stored here  
		else
		{
			tail->next = temp;
			tail = temp; 
		} 


		printf("Your Spot is Reserved!\n"); 		
	
	}

int duplicate(char *d)
{ 
		ENTRY *p; 
		p = head; 
		while(p != NULL)
		{
			if(strcmp( d , p->name) == 0 )
			{
					printf("Duplicate Name\n");
					return 1; 
			}
			p = p->next; 
		}
		return 0; 
			

}

void Delete(void)
	{
		ENTRY *p, *q;
 
		if(head == NULL)
			{
			printf("The Waiting List is Empty\n");
			return;
			} 
	
		int seats;
		printf("Enter Available Seating: ");
		scanf("%d", &seats);

		p = q = head;
		while(p != NULL && seats > 0) // checks every node in the list 
		{

			if(p->size <= seats)
			{
				printf("%s party of %d to table for %d\n", p->name, p->size, seats);
				seats -= p->size; 
				
				if(p == head) 			// removing first node
				{
					head = p->next; 	// moves head to the next node  
					free(p);
					p = q = head;
					if(head == NULL)	 // checks if there was only one node 
						tail = NULL; 	// makes the tail equal to null, almost resets the list 
				}	
				else 				// removing a node thats not in the front 
				{
					q->next = p-> next;	 // makes the next q to the node after p 
					free(p); 		// deletes p 
					p = q -> next; 		// makes p the next node after p 
					if( p == NULL) 		// checks if tail was deleted 
						tail = q;  
				}		
			}
			else
			{
				q = p; 
				p = p->next;
			}
		}


	}

void List(void)
	{ 
		if(head == NULL)
			{
			printf("The Waiting List is Empty\n");
			return; 
			} 

		ENTRY *p; 
		p = head; 
		while(p != NULL)
		{
			printf("%s party of %d\n", p->name, p->size); 
			p = p->next;
 

		}
	}

void fit_in(void)
	{
		ENTRY *p;
		if(head == NULL)
			{
			printf("The Waiting List is Empty\n");
			return;
			} 	
		
		else
			{		
				int party_size; 
				printf("Size? ");
				scanf("%d", &party_size); 
				printf("\n"); 
				
				p = head; 
				while( p != NULL) 
					{
						if(p -> size <= party_size)
							printf("%s, %d\n", p -> name, p -> size);
						p = p->next; 
					}		
			}

	}
