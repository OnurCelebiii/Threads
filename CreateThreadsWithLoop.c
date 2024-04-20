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
    pthread_t th[4];
    pthread_mutex_init(&mutex,NULL);

    for(int i = 0 ; i < 4 ; i++)
    {
        pthread_create(&th[i],NULL,&routine,NULL);
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("x = %d\n", x);
    
    return 0;
}
