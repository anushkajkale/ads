// Implement the solutions for following synchronization problems using semaphore:
// i. Producer Consumer 
// ii. Reader Writer 

// i. Producer Consumer

/*
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce a random item
        sem_wait(&empty);  // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex);  // Acquire the mutex to enter the critical section
        
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;  // Move to the next position in the buffer

        pthread_mutex_unlock(&mutex);  // Release the mutex to exit the critical section
        sem_post(&full);  // Signal that a slot in the buffer is full
    }
}

void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);  // Wait for a filled slot in the buffer
        pthread_mutex_lock(&mutex);  // Acquire the mutex to enter the critical section
        
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;  // Move to the next position in the buffer

        pthread_mutex_unlock(&mutex);  // Release the mutex to exit the critical section
        sem_post(&empty);  // Signal that a slot in the buffer is empty
    }
}


int main()
{   
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex
    sem_init(&empty, 0, BufferSize);  // Initialize the empty semaphore with the buffer size
    sem_init(&full, 0, 0);  // Initialize the full semaphore with 0

    int a[5] = {1, 2, 3, 4, 5};  // Just used for numbering the producer and consumer

    // Create producer threads
    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);
    }

    // Create consumer threads
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);
    }

    // Wait for producer threads to finish
    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    // Wait for consumer threads to finish
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);  // Destroy the mutex
    sem_destroy(&empty);  // Destroy the empty semaphore
    sem_destroy(&full);  // Destroy the full semaphore

    return 0;
}
*/

// ii. Reader Writer
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