#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 20
#define ENTRY struct entry
#define LIST struct list

void Insert(void);
void Delete(void); 
void List(void);
void fit_in(void);
void change(void); 
void clear(void);  
int duplicate(char *);

struct entry
{    
	char name[LENGTH];
	int size;
	ENTRY *next; 
}; 

struct list
{
	ENTRY *head; 
	ENTRY *tail; 
};

LIST list[4] = {{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};

int main()
	{
		int option = 1;


 
		while(option != 0)		// creates forever loop 
			{
				printf("\nResturaunt Waiting List\n	Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 5 - Change Size\n 0 - Exit\nEnter Option: "); 
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
						case 5: 
							change(); 
							break; 
						case 0:
							clear();   
							return 0; 
						default:
							printf("Invalid Input"); 
					} 
			}

	
	}	
	
void clear(void)
{
	int i; 
	for(i= 0; i<4;i++)
	{
		ENTRY *p; 
		p = list[i].head;
		while(p!= NULL)
		{
			
			list[i].head = p-> next; 
			free(p);
			p = list[i].head; 
		}
	} 
}
void Insert(void)
	{
		ENTRY *temp; 
		char n[LENGTH];
		int s, i;
 
		printf("Enter Name: "); 
		scanf ("%s", n);	  //user enters name and stores it in the current element 
			 
		if(duplicate(n)==1)  //goes to the duplicate function to look for duplicate names 
		{	
			printf("Duplicate Name\n"); 	
			return;
		}
	
 		printf("Enter Party Size: ");
		scanf("%d", &s);

		temp = (ENTRY *)malloc(sizeof(ENTRY));
 
		strcpy(temp->name, n); 
		temp->size = s;
		temp->next = NULL; 
		
		if(temp->size <=2 && temp->size >=1)
			i = 0;
		else if(temp->size <=4 && temp->size >= 3)
			i = 1; 
		else if(temp-> size <= 6 && temp->size >= 5)
			i = 2; 
		else if(temp->size >= 6) 
			i= 3; 
		
		if(list[i].head == NULL)
			list[i].head = list[i].tail = temp;  // since no memory is allocated in temp, the temp is stored here  
		else
		{
			list[i].tail->next = temp;
			list[i].tail = temp; 
		}
		 


		printf("Your Spot is Reserved!\n"); 		
	
	}

int duplicate(char *d)
{
		int i;
		ENTRY *p;
		for(i = 0; i< 4; i++)
		{  
			p = list[i].head; 
			while(p != NULL)
			{
				if(strcmp( d , p->name) == 0 )
				{
					return 1; 
				}
				p = p->next; 
			}
		} 
		return 0; 
			

}

void change(void)
{
	ENTRY *p, *q, *temp; 
	char name[LENGTH]; 
	int i, ns; 
	
	printf("Enter Name of Reservation: ");
	scanf("%s", name);
	
	if(duplicate(name) == 1)
	{
		temp = (ENTRY *)malloc(sizeof(ENTRY));
		strcpy(temp->name, name); 
	} 	
	for(i =0; i<4; i++)
	{
		p = q = list[i].head; 
		while(p!= NULL)
		{
			if(duplicate(name) == 1) 
			{
				if( p == list[i].head)
				{
					list[i].head = p->next; 
					free(p);
					p = q = list[i].head;
					if(list[i].head == NULL)
						list[i].tail = NULL;  	
				}
				else
				{
					q ->next = p->next;
					free(p);
					p = q->next; 
					if(p == NULL)
						list[i].tail = q; 
				}		
			}
			else
			{
				p = q;
				p = p->next;	
			}
		}	
	}
	printf("Enter New Size: ");
	scanf("%d", &ns); 
	temp->size = ns; 
	
	if( temp->size >= 1 && temp->size <= 2)
		i = 0;
	if(temp->size >= 3 && temp->size <= 4)
		i = 1; 
	if(temp->size >= 5 && temp->size <= 6)
		i = 2; 
	if(temp->size >= 6)
		i = 3; 
	
	if(list[i].head == NULL)
		list[i].head = list[i].tail = temp; 
	else
	{
		list[i].tail->next = temp; 
		list[i].tail = temp; 
	}
	printf("Your Reservation is Changed!\n");


		
}

void Delete(void)
	{
		int i;
		ENTRY *p, *q; 
 
		int seats;
		printf("Enter Available Seating: ");
		scanf("%d", &seats);
			
		for(i = 0; i<4; i++)
		{
			p = q = list[i].head;
			while(p != NULL && seats > 0) // checks every node in the list 
			{

				if(p->size <= seats)
				{
					printf("%s party of %d to table for %d\n", p->name, p->size, seats);
					seats -= p->size; 
				
					if(p == list[i].head) 			// removing first node
					{
						list[i].head = p->next; 	// moves head to the next node  
						free(p);
						p = q = list[i].head;
						if(list[i].head == NULL)	 // checks if there was only one node 
							list[i].tail = NULL; 	// makes the tail equal to null, almost resets the list 
					}	
					else 				// removing a node thats not in the front 
					{
						q->next = p-> next;	 // makes the next q to the node after p 
						free(p); 		// deletes p 
						p = q -> next; 		// makes p the next node after p 
						if( p == NULL) 		// checks if tail was deleted 
							list[i].tail = q;  
					}		
				}
				else
				{
					q = p; 
					p = p->next;
				}
			}
		}

	}

void List(void)
	{ 
		int i;
		int j = 1;  
		for(i = 0; i < 4; i++, j++)
		{
			ENTRY *p; 
			p = list[i].head; 
			while(p != NULL)
			{
				printf("%s party of %d\n", p->name, p->size); 
				p = p->next;

			}
		}
	}

void fit_in(void)
	{
		int i; 
		ENTRY *p;		
		int party_size; 
		printf("Size? ");
		scanf("%d", &party_size); 
		printf("\n"); 
		
		for(i= 0; i <4; i++) 
		{	
			p = list[i].head; 	
			while( p != NULL) 
			{
				if(p -> size <= party_size)
					printf("%s, %d\n", p -> name, p -> size);
				p = p->next; 
			}		
		}

	}
