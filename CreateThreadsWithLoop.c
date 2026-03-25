#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: pthread_create donusu kontrol edilmeli; basarisiz olusturulan
//       thread'lerin join edilmemesi tanimsiz davranisa yol acar.
// FIX:  Her pthread_create cagrisi kontrol ediliyor; hata durumunda
//       o ana kadar olusturulan thread'ler join edilip cikiliyor.

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

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        return 1;
    }

    int created = 0;
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("pthread_create failed");
            // Simdiye kadar olusturulan thread'leri bekle
            for (int j = 0; j < created; j++) {
                pthread_join(th[j], NULL);
            }
            pthread_mutex_destroy(&mutex);
            return 1;
        }
        created++;
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("x = %d\n", x);

    return 0;
}
//gcc -g -pthread CreateThreadsWithLoop.c -o loop
//./loop
