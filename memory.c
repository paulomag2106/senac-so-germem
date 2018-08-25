#include "memory.h"

void clearHeap() {
    printf("Clearing Heap...\n");
    for(int i = 0; i < HEAPSIZE; ++i)
        heap[i] = 0;
}

void printHeap() {
    printf("HEAP ALLOCATION:");
    for(int i = 0; i < HEAPSIZE; ++i) {
        if(i%(16) == 0)
            printf("\n");
        printf("%02X ", heap[i]);
    }
    printf("\n");
}

bool isFree(uint32_t at, uint32_t stride) {
    // printf("Address: %d, Amount to allocate: %d\n", at, stride);

    for(int i = at; i < at+stride; ++i) {
        if(heap[i] != 0 || i > HEAPSIZE) {
            // printf("Not enough space here\n");
            return false;
        }
    }

    return true;
}

void *mem_alloc(size_t size) {
    for(int i = 0; i < HEAPSIZE;) {
        if(isFree(i, size+2)) {
            printf("Allocating Memory...\n");
            heap[i++] = (uint8_t)(size >> 8) & 0xff;
            heap[i++] = (uint8_t)(size) & 0xff;
            return heap+i;
        } else {
            int offset = 256*heap[i] + heap[i+1]+2;
            i += offset;
            // printf("Jumping %d bytes\n", offset);
        }
    }

    printf("Not enough memory on heap\n");
    return NULL;
}

void mem_free(void *pointer) {
    if(pointer != NULL) {
        printf("Freeing Memory...\n");
        uint8_t *reference = pointer;
        int size = (int)((*(reference-2) * 256) + (*(reference-1)));
        for(int i = 0; i < size+2; ++i) {
            reference[i-2] = 0;
            reference[i-1] = 0;
        }
        pointer = NULL;
    } else {
        printf("Pointer already freed!\n");
    }
}
