#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[10] ={3,5,9,1,4,8,0,2,7,6};

void *arrySort(void *arg) {
    int index = *(int*)arg;

    // Bubble sort implementation for sorting 5 elements
    for (int i = index; i < index + 5; i++) {
        for (int j = index; j < index + 5 - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    return arg;
}

void *arrMergeSort(void *arg) {
    int i = 0;
    int j = 5;
    int temp[10];

    for (int k = 0; k < 10; k++) {
        if (i < 5 && j < 10) {
            if (arr[i] < arr[j]) {
                temp[k] = arr[i++];
            } else {
                temp[k] = arr[j++];
            }
        } else if (i < 5) {
            temp[k] = arr[i++];
        } else {
            temp[k] = arr[j++];
        }
    }

    // Copy the merged array back to the original array
    for (int k = 0; k < 10; k++) {
        arr[k] = temp[k];
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    pthread_t th[3];

    for(int i = 0 ; i < 2 ; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        pthread_create(&th[i],NULL,&arrySort,a);
    }

    pthread_create(&th[2],NULL,&arrMergeSort,NULL);

    for(int i = 0 ; i < 3 ; i++)
    {
        pthread_join(th[i], NULL);
    }

    for(int i = 0 ; i < 10 ; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
