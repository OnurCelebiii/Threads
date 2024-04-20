#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex;

void *routine(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        x++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("x = %d\n", x);
    
    return 0;
}
//gcc -g -pthread file.c -o file
//./file.exe
