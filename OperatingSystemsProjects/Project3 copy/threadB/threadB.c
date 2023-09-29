#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TIMES 10

void *printA();
void *printB();

pthread_t threadA, threadB;
pthread_mutex_t lock;

int main()
{
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n Mutex initialization failed\n"); 
        return 1; 
    } 

    pthread_create(&threadA, NULL, printA, NULL);
    pthread_create(&threadB, NULL, printB, NULL);
    
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    
    pthread_mutex_destroy(&lock);

    return 0;
}

void *printA() {
    for (int i = 0; i < TIMES; i++) {
        pthread_mutex_lock(&lock);
        for (int j = 0; j < 5; j++) {
            printf("%d: %s\n", i+1, "AAAAAAAAA");
            usleep(1000);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
    }
    return NULL;

}

void *printB() {
    for (int i = 0; i < TIMES; i++) {
        pthread_mutex_lock(&lock);
        for (int j = 0; j < 5; j++) {
            printf("%d: %s\n", i+1, "BBBBBBBBB");
            usleep(1000);
        }
        printf("\n");
        pthread_mutex_unlock(&lock);
    }
    return NULL;

}
