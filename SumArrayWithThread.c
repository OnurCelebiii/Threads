#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[10] ={3,5,9,1,4,8,0,2,7,6};

void *sumArry(void *arg) {

    int index = *(int*)arg;

    int sum = 0;
    for (int i = 0 ; i < 5 ; i++)
    {
        sum += arr[index+i];
    }

    *(int*)arg = sum;

    return arg;
}


int main(int argc, char *argv[]) {
    pthread_t th[2];

    for(int i = 0 ; i < 2 ; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        pthread_create(&th[i],NULL,&sumArry,a);
    }

    int globalSum = 0;
    for(int i = 0 ; i < 2 ; i++)
    {
        int *result;
        pthread_join(th[i], (void **)&result);
        globalSum += *result;
        free(result);
    }

    printf("result of sum : %d", globalSum);
    return 0;
}
