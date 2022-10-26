#include <assert.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

sem_t empty_slot;
sem_t filled_slot;

#define P sem_wait
#define V sem_post
#define NTHREAD 64

void producer() {
    while (1) {
        P(&empty_slot);
        printf("(");
        V(&filled_slot);
    }
}

void consumer() {
    while (1) {
        P(&filled_slot);
        printf(")");
        V(&empty_slot);
    }
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    sem_init(&filled_slot, 0, 0);
    sem_init(&empty_slot, 0, atoi(argv[1]));
    for (int i = 0; i < 8; i++) {
        create(producer);
        create(consumer);
    }
}
