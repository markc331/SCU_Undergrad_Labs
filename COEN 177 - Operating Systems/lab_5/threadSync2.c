// Thread Sychronization

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock; 

void* go(void* arg) { 
   pthread_mutex_lock(&lock);
   printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1); 
   pthread_mutex_unlock(&lock); 
  return (NULL);
} 

int main() { 
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
return 0; 
} 
