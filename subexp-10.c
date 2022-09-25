#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

sem_t empty_slot;
sem_t filled_slot;

#define P sem_wait
#define V sem_post
#define NTHREAD 64

enum {
    T_FREE = 0,
    T_LIVE,
    T_DEAD,
};
struct thread {
    int id, status;
    pthread_t thread;
    void (*entry)(int);
};

struct thread tpool[NTHREAD], *tptr = tpool;

void *wrapper(void *arg) {
    struct thread *thread = (struct thread *)arg;
    thread->entry(thread->id);
    return NULL;
}

void create(void *fn) {
    assert(tptr - tpool < NTHREAD);
    *tptr = (struct thread){
        .id = tptr - tpool + 1,
        .status = T_LIVE,
        .entry = fn,
    };
    pthread_create(&(tptr->thread), NULL, wrapper, tptr);
    ++tptr;
}

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
