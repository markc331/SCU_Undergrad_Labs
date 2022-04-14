#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LENGTH 20
#define ENTRY struct entry
#define LIST struct list

void Insert(char *, int);
void Delete(void); 
void List(void);
void fit_in(void);
void reverse(void); 
void save(char *);  
void read_file(char *);  
int duplicate(char *p);
void *auto_save(void *); 
void read_auto_save(char *); 
struct entry
{    
	char name[LENGTH];
	int size;
	ENTRY *next; 
}; 

ENTRY *head = NULL; 
ENTRY *tail = NULL; 
pthread_mutex_t mutex; 
void rev_name(char *); 
void rev_list(ENTRY *);
void clear(ENTRY *);
int main(int argc, char *argv[])
	{
		int option = 1, s;
		char n[LENGTH];
		if(argc == 1)
		{
			printf("The name of the file is missing!\n"); 
			return 1; 	
		}
		pthread_t thr; 
		pthread_mutex_init(&mutex, NULL); 
		pthread_create(&thr, NULL, auto_save,(void *)argv[2]); 
		read_file(argv[1]);


 
		while(option != 0)		// creates forever loop 
			{
				printf("\nResturaunt Waiting List\n	Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 5 - Reverse list\n 6 - Backwords Name\n 7 - Read Auto Save\n 0 - Save & Exit\nEnter Option: "); 
				scanf("%d" ,  &option);	//user inputs option 
				printf("\n");
					
				switch(option)
					{
						case 1: 
					                printf("Enter Name: ");
					                scanf("%s", n);          //user enters name and stores it in the current element

        					        if(duplicate(n)==1)  //goes to the duplicate function to look for duplicate names
        					        {
                        					printf("Duplicate Name\n");
                      						break;
                					}

              						printf("Enter Party Size: ");
               						scanf("%d", &s);


							Insert(n, s); 	//refers to insert function 
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
							rev_list(head);
							break;
						case 6: 
							reverse();
							break;
						case 7: 
							read_auto_save(argv[2]);
							break;  
						case 0:
							pthread_mutex_lock(&mutex); 
							pthread_cancel(thr);
							pthread_mutex_unlock(&mutex); 
							save(argv[1]);
							clear(head);   
							return 0; 
						default:
							printf("Invalid Input"); 
					} 
			}

	
}
void *auto_save(void *arg) 
{
	ENTRY *p; 
	char *fname = (char *)arg; 
	while(1)
	{
		sleep(15); 
		pthread_mutex_lock(&mutex); 
		FILE *fp = fopen(fname, "wb"); 
		p = head; 
		while(p != NULL)
		{
			fwrite(p, sizeof(ENTRY), 1, fp); 
			p = p->next;
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex); 
	}
}
void read_auto_save(char *binfile)
{
        ENTRY p;
        FILE *fp = fopen(binfile, "rb");
        pthread_mutex_lock(&mutex);
        while(fread(&p, sizeof(ENTRY), 1, fp) == 1)
        {
                printf("%s party of %d\n", p.name, p.size);
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);
}

void reverse(void)
{
	ENTRY *p = head;
	while(p != NULL)
	{
		pthread_mutex_lock(&mutex);
		rev_name(p->name);
		printf("\n");
		p = p->next; 
		pthread_mutex_unlock(&mutex); 
	}
}

void rev_name(char *n)
{
	if( *n != '\0'){
		rev_name(n+1);
		printf("%c", *n);
	}

}
void rev_list(ENTRY *p)
{ 
	if(p == NULL)
		return;
	rev_list(p->next);
	printf("%s party of %d\n", p->name, p->size);
}	
void save(char *file)
{
	ENTRY *p; 
	FILE *fp;
	fp = fopen(file, "w"); //opens file for writing
	p = head;  
	while(p != NULL) // transverse through the list
	{
		fprintf(fp,"%s\t%d\n", p->name, p->size); // copies current node to the file
		p = p->next; 
	}
	fclose(fp); 
} 

void read_file(char p[])
{ 
	FILE *fp;
	if((fp = fopen(p, "r")) == NULL) //checks if file exist
	{
		printf("Starting with Empty List\n");
		return; 
	}
	char n[LENGTH];
	int s; 
	while((fscanf(fp, "%s%d", n, &s))==2) // looks through the file
	{
 		Insert(n, s); // sends what ever is in the file to the insert function
	}
	fclose(fp); 
}
void clear(ENTRY *p)
{ 
	if(p == NULL)
		return; 
	clear(p->next); 
	free(p);
}

void Insert(char *nombre, int s)
{
	ENTRY *temp; 
	temp = (ENTRY *)malloc(sizeof(ENTRY));
 
	strcpy(temp->name, nombre); 
	temp->size = s;
	temp->next = NULL; 
	
	pthread_mutex_lock(&mutex); 	
	if(head == NULL)
		head = tail = temp;  // since no memory is allocated in temp, the temp is stored here  
	else
	{
		tail->next = temp;
		tail = temp; 
	} 

	pthread_mutex_unlock(&mutex); 
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
			return 1; 
		}
		p = p->next; 
	}
	return 0; 
}  

void Delete(void)
{
	ENTRY *p, *q; 
 
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
			pthread_mutex_lock(&mutex); 	
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
			pthread_mutex_unlock(&mutex);
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
	ENTRY *p; 
	p = head; 
	while(p != NULL)
	{
		pthread_mutex_lock(&mutex); 
		printf("%s party of %d\n", p->name, p->size); 
		p = p->next;
		pthread_mutex_unlock(&mutex); 

	}
}

void fit_in(void)
{ 
	ENTRY *p;		
	int party_size; 
	printf("Size? ");
	scanf("%d", &party_size); 
	printf("\n"); 
		
	p = head; 	
	while( p != NULL) 
	{
		pthread_mutex_lock(&mutex); 
		if(p -> size <= party_size)
			printf("%s, %d\n", p -> name, p -> size);
		p = p->next; 
		pthread_mutex_unlock(&mutex); 
	}		
}
