#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20


void Insert(void);
void Delete(void); 
void List(void);
void fit_in(void); 
int duplicate(char *);

typedef struct entry
	{    
		char name[LENGTH];
		int size;
	}ENTRY; 

ENTRY list[SIZE];

int counter = 0; 


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
					} 
			}

	
	}	
	

void Insert(void)
	{
		ENTRY *p = list; 
		char n[LENGTH];
		if(counter != SIZE)			
			{

				int i; 
				
				printf("Enter Name: "); 
				scanf ("%s", n);	  //user enters name and stores it in the current element 
			
				if(duplicate(n)==1)  //goes to the duplicate function to look for duplicate names 
					return;

				strcpy(list[counter].name, n); 
 				printf("Enter Party Size: ");
				scanf("%d", &list[counter].size);

				counter++;  
				printf("Your Spot is Reserved!\n"); 
			} 			
	
		else
			printf("The Waiting List is Empty\n");
	}

int duplicate(char *d)
{
		ENTRY *p = list; 
		int i; 
		
		for(i =0; i<counter; i++, p++)
		{
			if((strcmp( d , p->name)) == 0)
			{
				printf("Duplicate Name.\n"); 
				return 1;  
			}
		}	 
		return 0; 

}

void Delete(void)
	{
		ENTRY *p = list; 
		if(counter == 0)
				printf("The Waiting List is Empty\n"); 
		else 
			{
				int seats;
				printf("Enter Available Seating: ");
				scanf("%d", &seats);

				int i; 
				for(i= 0; i < counter; i++)
					{
						if(list[i].size <= seats)
						{
							printf("%s party of %d to table for %d\n", list[i].name, list[i].size, seats);
							seats -= list[i].size; 

							int j; 
							for(j = i; j < counter; j++)
								{
									strcpy(list[j].name,list[j+1].name);
									list[j].size = list[j+1].size;	
									
								} 
							counter--;
							i--;  
						}
					}
	
			}

	}

void List(void)
	{
		ENTRY *p = list;
		if(counter == 0 )			//checks if anything was entered into list 
			printf("The Waiting List is Empty\n");
 
		int i;
		for(i = 0; i < counter; i++, p++) 					//lists all saved entries
		{
			printf("%d.  %s party of  %d\n", i+1, p->name, p->size);	//prints list 

		}
	}

void fit_in(void)
	{
		ENTRY *p = list;
		if(counter == 0)
			printf("The Waiting List is Empty\n");	
		
		else
			{		
				int party_size; 
				printf("Size? ");
				scanf("%d", &party_size); 
				printf("\n"); 
				
				int i; 
				for(i = 0; i< counter; i++, p++) 
					{
						if(p -> size <= party_size)
							printf("%s, %d\n", p -> name, p -> size);

					}
		
			}
	}
