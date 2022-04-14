// Producer - Consumer with condition variable

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
pthread_mutex_t mutex;
pthread_cond_t full, empty; 
int p, c, in, out, count; 

void *producer(void *arg) {
    int item;
    int p = (int)arg;
    srand(time(0));
    do {
        item = (rand() % 100);  // random number for producer
        pthread_mutex_lock(&mutex);
        while(count == BUFSIZE)
		pthread_cond_wait(&empty, &mutex);
        buff[in] = item;
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
        in = (in + 1) % BUFSIZE;
        count++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    } while (1);
    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;
    srand(time(0));
    do {
        pthread_mutex_lock(&mutex);
        while (count == 0)
	    pthread_cond_wait(&full, &mutex);
        item = buff[out];
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
	out = (out +1) % BUFSIZE;
        count--;	
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(12);
    } while (1);
    pthread_exit(0);
}

int main () {
    //your code to create mutex lock and empty and full condition variables 
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
    for (p = 0; p < NP; p++)
        pthread_create (&tidP[p], NULL, producer, (void*)(size_t)p);
    for (c = 0; c < NC; c++)
        pthread_create (&tidC[c], NULL, consumer, (void*)(size_t)c);
    // main thread waiting for consumer and producer threads to complete their tasks
    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
}

