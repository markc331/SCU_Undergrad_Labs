#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20


void Insert(void);
void Delete(void); 
void List(void);    
char name[SIZE][LENGTH];
int sizes[SIZE];
int counter = 0; 
int main()
	{
		int option = 1;

		int c;
		for(c = 0; c<5; c++)
			{
				name[c][0] = '\0'; //sets everything to null until something is entered
			} 
		while(option != 0)		// creates forever loop 
			{
				printf("\nResturaunt Waiting List\n	Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 0 - Exit\nEnter Option: "); 
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
					} 
			}

	
	}	
	

void Insert(void)
	{
		if(counter != 10)			//max number of entries 
			{
				printf("Enter Name: "); 
				scanf ("%s", name[counter]);	  //user enters name and stores it in the current element 
			
				printf("Enter Party Size: ");
				scanf("%d", &sizes[counter]);   // enter party size and saves in current element 
				counter++;
				printf("Your Spot is Reserved!\n"); 
			}
	
			else
				printf("The Waiting List is Full\n"); 
	}


void Delete(void)
	{
		if(name[0][0] == '\0' && sizes[0] == 0)
				printf("The Waiting List is Empty\n"); 
		else 
			{
				int seats;
				printf("Enter Available Seating: ");
				scanf("%d", &seats);

				for(int i = 0; i < counter; i++)
					{
						if(sizes[i] <= seats)
						{
							printf("%s party of %d to table for %d\n", name[i], sizes[i], seats);
							seats -= sizes[i]; 

							for(int j = i; j < counter; j++)
								{
									strcpy(name[j],name[j+1]);
									sizes[j] = sizes[j+1];	
									
								} 
							counter--;
							i--;  
						}
					}
	
			}

	}
	

void List(void)
	{

		if(counter == 0 )			//checks if anything was entered into list 
			printf("The Waiting List is Empty\n");

		int i;
		for(i = 0; i < counter; i++) 					//lists all saved entries
		{

			printf("%d.  %s party of  %d\n", i+1, name[i], sizes[i]);	//prints list 

		}
	}

