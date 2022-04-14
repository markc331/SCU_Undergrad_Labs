// Producer - Consumer with semaphores
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>

#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
sem_t *mutex, *full, *empty; 
int p, c, in, out; 

void *producer(void *arg) {
    int item;
    int p = (int*)arg;
    srand(time(0));
    do {
        item = (rand() % 100);  // random number for producer
        sem_wait(empty);
        sem_wait(mutex);
	buff[in] = item;
	in = (in + 1) % BUFSIZE;
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
        sleep(5);
        
        sem_post(mutex);
        sem_post(full);
    } while (1);
    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    srand(time(0));
    int c = (int*)arg;
    do {
        sem_wait(full);
        sem_wait(mutex);
        item = buff[out];
	out = (out + 1) % BUFSIZE;

        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
        sleep(10);	
        sem_post(mutex);
        sem_post(empty);
    } while (1);
    pthread_exit(0);
}
void cleanup(int sigtype)
{
	sem_unlink("mutex");
	sem_unlink("empty");
	sem_unlink("full");
	printf("\nTerminating\n");
	exit(0);
}

int main () {
    signal(SIGINT, cleanup);
    //your code to create mutex, empty, and full semaphoresi
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE);
    full = sem_open("full", O_CREAT, 0644, 0);

    for (p = 0; p < NP; p++)
        pthread_create (&tidP[p], NULL, producer, (void*)(size_t)p);

    for (c = 0; c < NC; c++)
        pthread_create (&tidC[c], NULL, consumer, (void*)(size_t)c);

    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    return 0;
}
