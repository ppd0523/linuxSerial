#pragma once

#include <stdint.h>

#define QUEUE_SIZE 10

#define DATA_TYPE uint8_t

void push(DATA_TYPE* src, int n);
int pop(DATA_TYPE* dest, int n);
int pop(DATA_TYPE* dset);