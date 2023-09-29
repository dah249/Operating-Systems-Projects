#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  

#define TIMES 10

void *printA();
void *printB();

pthread_t threadA, threadB;

int main()
{
    pthread_create(&threadA, NULL, printA, NULL);
    pthread_create(&threadB, NULL, printB, NULL);
    
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    
    return 0;
}

void *printA() {
    for (int i = 0; i < TIMES; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d: %s\n", i+1, "AAAAAAAAA");
            usleep(1000);
        }
        printf("\n");
    }
    return NULL;
}

void *printB() {
    for (int i = 0; i < TIMES; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d: %s\n", i+1, "BBBBBBBBB");
            usleep(1000);
        }
        printf("\n");

    }
    return NULL;
}






