#include <string.h>

#include "queue.h"

static DATA_TYPE queue[QUEUE_SIZE];
static int f = 0, r = 0;
static int nextR = 0, nextF = 0;
static int empty = QUEUE_SIZE - 1;
static int len = 0;

static int half = 0;

void push(DATA_TYPE* src, int n){
    if(n <= empty){
        empty -= n;
        len += n;
        nextR = (r + n) % QUEUE_SIZE;
        if(nextR > f){
            memcpy(&queue[r], &src, n);
        }
        else{
            half = QUEUE_SIZE - r;
            memcpy(&queue[r], &src, half);
            memcpy(&queue, &src[half], n-half);
        }
        
        r = nextR;
    } 
    else {
        return;
    }
}

int pop(DATA_TYPE* dest, int n){
    if(n <= len){
        len -= n;
        empty += n;
        nextF = (f + n) % QUEUE_SIZE;
        if(nextF < r){
            memcpy(&dest, &queue[f], n);
        }
        else{
            half = QUEUE_SIZE - f;
            memcpy(&dest, &queue[f], half);
            memcpy(&dest[half], &queue, n-half);
        }

        f = nextF;

        return n;
    }
    else{
        return -1;
        //elements < n
    }
}