#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

static unsigned long counter = 0;

void bar(void) {
    counter++;
}

void foo(void) {
    bar();
}

static bool running = true;

void* thread_func(void* data) {
    (void)data;

    while (running) {
        foo();
        // usleep(1);
    }

    return NULL;
}

#define THREAD_COUNT 4

int main() {
    printf("foo: %p\n", foo);
    printf("bar: %p\n", bar);

    pthread_t threads[THREAD_COUNT];
    
    for (int i = 0; i < THREAD_COUNT; i++) {
        errno = pthread_create(&threads[i], NULL, thread_func, NULL);
        if (errno != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    while (true) {
        if (getchar() == 'q') {
            break;
        }
    }

    running = false;

    for (int i = 0; i < THREAD_COUNT; i++) {
        errno = pthread_join(threads[i], NULL);
        if (errno != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("final counter value is %ld\n", counter);
}
