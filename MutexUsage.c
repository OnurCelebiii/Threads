#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: pthread_mutex_init ve pthread_create donusleri kontrol edilmeli.
// FIX:  Hata kontrolu eklendi; basarisiz olursa program erken cikiyor.

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

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        return 1;
    }

    if (pthread_create(&t1, NULL, routine, NULL) != 0) {
        perror("pthread_create t1 failed");
        pthread_mutex_destroy(&mutex);
        return 1;
    }
    if (pthread_create(&t2, NULL, routine, NULL) != 0) {
        perror("pthread_create t2 failed");
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("x = %d\n", x);

    return 0;
}
//gcc -g -pthread MutexUsage.c -o mutex
//./mutex
