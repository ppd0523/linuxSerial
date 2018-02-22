#pragma once

#include <stdint.h>

#define QUEUE_SIZE 4096

typedef uint8_t Data_t;

void push(Data_t* src, int n);
int pop(Data_t* dest, int n);
int pop(Data_t* dest);