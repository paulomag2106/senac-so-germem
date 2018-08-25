#pragma once
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define HEAPSIZE 8192
uint8_t heap[HEAPSIZE];

void clearHeap();
void printHeap();
bool isFree(uint32_t at, uint32_t stride);
void *mem_alloc(size_t size);
void mem_free(void *pointer);
