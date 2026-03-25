#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// TODO: merge thread, sort thread'leriyle ayni anda baslatiliyor.
//       Sort thread'leri bitmeden merge calismaya baslarsa veri bozulur
//       (race condition).
// FIX:  Sort thread'leri once join ediliyor, ardindan merge thread'i
//       baslatiliyor. Boylece merge her zaman sirali veri uzerinde calisir.

// TODO: arrySort thread'lerine gecilen malloc belleginin serbest birakilmasi
//       unutulmus; bellek sizintisi olusuyordu.
// FIX:  Her sort thread join edildikten sonra arg pointer'i free ediliyor.

int arr[10] = {3, 5, 9, 1, 4, 8, 0, 2, 7, 6};

void *arrySort(void *arg) {
    int index = *(int *)arg;

    // Bubble sort: dizinin ilgili yarisini sirala
    for (int i = index; i < index + 5; i++) {
        for (int j = index; j < index + 4; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j]   = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return arg;
}

void *arrMergeSort(void *arg) {
    (void)arg;
    int i = 0, j = 5;
    int temp[10];

    // Sirali iki yarıyı birlestir
    for (int k = 0; k < 10; k++) {
        if (i < 5 && j < 10) {
            temp[k] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
        } else if (i < 5) {
            temp[k] = arr[i++];
        } else {
            temp[k] = arr[j++];
        }
    }

    for (int k = 0; k < 10; k++) {
        arr[k] = temp[k];
    }

    return NULL;
}

int main(void) {
    pthread_t sortTh[2];

    // 1. Adim: iki sort thread'ini olustur
    for (int i = 0; i < 2; i++) {
        int *a = malloc(sizeof(int));
        if (a == NULL) {
            perror("malloc failed");
            return 1;
        }
        *a = i * 5;
        if (pthread_create(&sortTh[i], NULL, &arrySort, a) != 0) {
            perror("pthread_create (sort) failed");
            free(a);
            return 1;
        }
    }

    // 2. Adim: sort thread'leri bitmesini bekle, ardindan bellegini serbest birak
    for (int i = 0; i < 2; i++) {
        void *retval;
        pthread_join(sortTh[i], &retval);
        free(retval);   // arrySort, arg pointer'ini geri dondurur
    }

    // 3. Adim: her iki yari sirali olduktan sonra merge thread'ini baslat
    pthread_t mergeTh;
    if (pthread_create(&mergeTh, NULL, &arrMergeSort, NULL) != 0) {
        perror("pthread_create (merge) failed");
        return 1;
    }
    pthread_join(mergeTh, NULL);

    // Sonucu yazdir
    for (int i = 0; i < 10; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
//gcc -g -pthread ThreadSortingAlgorithm.c -o sort
//./sort
