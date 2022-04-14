#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20


void Insert(void);
void Delete(void); 
void List(void);
void fit_in(void); 
int duplicate(char *);

typedef union extra 
{
	char bday_names[20];
	int years;
	float avg_age;
}EXTRA; 

typedef struct entry
	{    
		char name[LENGTH];
		int size;
		int occasion;
		EXTRA extra_info; 
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
				printf("Occasion? ");
				scanf("%d", &list[counter].occasion); 
	
				switch(list[counter].occasion)
				{
					case 1: 
						printf("Name of the Birthday Person: ");
						scanf("%s", list[counter].extra_info.bday_names);
						break; 

					case 2: 
						printf("How Many Years? ");
						scanf("%d", &list[counter].extra_info.years);
						break;  
				}
				
				if(list[counter].occasion != 1 && list[counter].occasion != 2)
				{
					printf("Average Age? ");
					scanf("%f", &list[counter].extra_info.avg_age); 
				}	
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
			if((strcmp( d , p->name)) == 0) //compares the entered name to previously stored names to check if they match 
			{
				printf("Duplicate Name.\n"); 
				return 1; // returns 1 if there is a duplicate 
			}
		}	 
		return 0; // returns 0 if there isnt a duplicate 

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
				for(i= 0; i < counter; i++,p++)
					{
						if(p->size <= seats)
						{
							printf("%s party of %d to table for %d\n", p->name, p->size, seats); 
							seats -= p->size; 

							int j; 
							for(j = i; j < counter; j++)
								{
									strcpy(list[j].name,list[j+1].name);		// from this line down it copies whatever was in the next postion to the current postion 
									list[j].size = list[j+1].size;
									list[j].occasion = list[j+1].occasion; 
								 	strcpy(list[j].extra_info.bday_names, list[j+1].extra_info.bday_names); 
									list[j].extra_info.years = list[j+1].extra_info.years;
									list[j].extra_info.avg_age = list[j+1].extra_info.avg_age;	
									
								} 
							counter--;
							i--;  
							p--; 
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
			if(p->occasion == 1)
				printf("%d.  %s party of %d, Occasion: %d, %s's Birthday\n", i+1, p->name, p->size, p->occasion, p->extra_info.bday_names);	//prints list if occasion is birthday 

			if(p->occasion == 2) 
				printf("%d.  %s party of %d, Occasion: %d, %d Year Anniversary\n", i+1, p->name, p->size, p->occasion, p->extra_info.years);  // prints list if occasion is anniversary 
	
			if(p->occasion != 1 && p-> occasion != 2)
				printf("%d.  %s party of %d, Occasion: %d, %f\n", i+1, p->name, p->size, p->occasion, p->extra_info.avg_age);   // prints list if occasion is other 
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
						{
							if(p->occasion ==1)
								printf("%s, %d, %d, %s\n", p -> name, p -> size, p->occasion, p->extra_info.bday_names); // if the occasion is a birthday it prints
							if(p->occasion ==2)
								printf("%s, %d, %d, %d\n", p-> name, p-> size, p->occasion, p->extra_info.years); // if the occasion is an anniversary it prints the corresponding details
							if(p->occasion != 1 && p-> occasion != 2)
								printf("%s, %d, %d, %f\n", p->name, p->size, p->occasion, p->extra_info.avg_age); // if the occasion is other then it prints corresponding details 
						}
					}
		
			}
	}
