#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *welcomeThreads(void *arg) {
    printf("Welcome Threads\n");
    sleep(3);
    printf("Goodbye Threads\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, welcomeThreads, NULL);
    pthread_create(&t2, NULL, welcomeThreads, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
