// Implement the solutions for following synchronization problems using semaphore:
// i. Reader Writer 
// ii. Dinning Philosopher 

// i. Reader Writer

/*
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    cnt = cnt * 2;
    printf("Writer %d modified cnt to %d\n", *((int *)wno), cnt);
    sem_post(&wrt);
    return NULL; // Added return statement
}

void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this is the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);

    // Reading Section
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
    
    return NULL; // Added return statement
}

int main()
{   
    pthread_t read[10], write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Just used for numbering the readers and writers

    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, reader, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
*/

// ii. Dining Philosopher
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t chopstick[5];
void *philos(void *);
void eat(int);
int main()
 {
         int i,n[5];
         pthread_t T[5];
         for(i=0;i<5;i++)
         sem_init(&chopstick[i],0,1);
         for(i=0;i<5;i++){
                 n[i]=i;
                 pthread_create(&T[i],NULL,philos,(void *)&n[i]);
                 }
         for(i=0;i<5;i++)
                 pthread_join(T[i],NULL);
 }      
void *philos(void *n)
 {
         int ph=*(int *)n;
         printf("Philosopher %d wants to eat\n",ph);
         printf("Philosopher %d tries to pick left chopstick\n",ph);
         sem_wait(&chopstick[ph]);
         printf("Philosopher %d picks the left chopstick\n",ph);
         printf("Philosopher %d tries to pick the right chopstick\n",ph);
         sem_wait(&chopstick[(ph+1)%5]);
         printf("Philosopher %d picks the right chopstick\n",ph);
         eat(ph);
         sleep(2);
         printf("Philosopher %d has finished eating\n",ph);
         sem_post(&chopstick[(ph+1)%5]);
         printf("Philosopher %d leaves the right chopstick\n",ph);
         sem_post(&chopstick[ph]);
         printf("Philosopher %d leaves the left chopstick\n",ph);
 }
 void eat(int ph)
 {
         printf("Philosopher %d begins to eat\n",ph);
 }