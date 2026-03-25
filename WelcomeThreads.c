#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// TODO: getpid() tum thread'ler icin ayni PID'i dondurur (ayni process'teler).
//       Thread kimligini gostermek icin pthread_self() kullanilmali.
// FIX:  pthread_self() ile her thread'in benzersiz ID'si gosteriliyor.

// TODO: pthread_create hatasi kontrol edilmeli.
// FIX:  Donus degeri kontrol edilerek hata durumunda program sonlandiriliyor.

void *welcomeThreads(void *arg) {
    printf("Welcome Threads - Thread ID: %lu\n", (unsigned long)pthread_self());
    sleep(3);
    printf("Goodbye Threads - Thread ID: %lu\n", (unsigned long)pthread_self());
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, welcomeThreads, NULL) != 0) {
        perror("pthread_create t1 failed");
        return 1;
    }
    if (pthread_create(&t2, NULL, welcomeThreads, NULL) != 0) {
        perror("pthread_create t2 failed");
        return 1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
//gcc -g -pthread WelcomeThreads.c -o welcome
//./welcome
