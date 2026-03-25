#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: printf sonunda '\n' eksik; cikti satir sonu olmadan biter.
// FIX:  '\n' eklendi.

// TODO: pthread_create donusu kontrol edilmeli; basarisiz thread join
//       edilirse tanimsiz davranis olusur.
// FIX:  Hata kontrolu eklendi; basarisiz thread icin malloc bellegini
//       serbest birakip cikiliyor.

int arr[10] = {3, 5, 9, 1, 4, 8, 0, 2, 7, 6};

void *sumArray(void *arg) {
    int index = *(int *)arg;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr[index + i];
    }
    *(int *)arg = sum;
    return arg;
}

int main(void) {
    pthread_t th[2];
    int *args[2];

    for (int i = 0; i < 2; i++) {
        args[i] = malloc(sizeof(int));
        if (args[i] == NULL) {
            perror("malloc failed");
            // Onceki tahsisleri serbest birak
            for (int j = 0; j < i; j++) free(args[j]);
            return 1;
        }
        *args[i] = i * 5;

        if (pthread_create(&th[i], NULL, &sumArray, args[i]) != 0) {
            perror("pthread_create failed");
            free(args[i]);
            // Onceki thread'leri temizle
            for (int j = 0; j < i; j++) {
                int *result;
                pthread_join(th[j], (void **)&result);
                free(result);
            }
            return 1;
        }
    }

    int globalSum = 0;
    for (int i = 0; i < 2; i++) {
        int *result;
        pthread_join(th[i], (void **)&result);
        globalSum += *result;
        free(result);
    }

    printf("Result of sum: %d\n", globalSum);
    return 0;
}
//gcc -g -pthread SumArrayWithThread.c -o sum
//./sum
