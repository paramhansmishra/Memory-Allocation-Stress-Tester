#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // usleep

int main(void) {
    const size_t CHUNK = 1024 * 1024; // 1 MB per allocation
    size_t capacity = 1024;           // initial pointer array capacity
    void **arr = malloc(capacity * sizeof(void*));
    if (!arr) return 1;

    size_t count = 0;
    while (1) {
        if (count == capacity) {
            capacity *= 2;
            void **tmp = realloc(arr, capacity * sizeof(void*));
            if (!tmp) {
                printf("Failed to grow pointer array after %zu MB\n", count);
                break;
            }
            arr = tmp;
        }

        void *p = malloc(CHUNK);
        if (!p) {
            printf("malloc() failed after allocating ~%zu MB\n", count);
            break;
        }

        // Touch memory so Linux actually maps physical pages (avoids overcommit illusion)
        memset(p, 0xAA, CHUNK);

        arr[count++] = p;

        // Print status occasionally (reduce terminal flood)
        if (count % 10 == 0) {
            printf("Allocated ~%zu MB\n", count); // count*1MB
            fflush(stdout);
        }

        // slow it down a bit so you can watch and interrupt if needed
        usleep(100000); // 100 ms
    }

    printf("Stopped at ~%zu MB\n", count);
    fflush(stdout);

    // intentionally not freeing arr/pointers so state is preserved until process end
    pause(); // wait here so you can inspect process from another terminal if desired
    return 0;
}
