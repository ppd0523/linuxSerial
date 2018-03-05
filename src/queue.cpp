#include <string.h>

#include "queue.h"

static Data_t queue[QUEUE_SIZE];
static int f = 0, r = 0;
static int nextR = 0, nextF = 0;
static int empty = QUEUE_SIZE - 1;
static int len = 0;

static int half = 0;

void push(Data_t* src, int n){
    if(n <= empty){
        empty -= n;
        len += n;
        nextR = (r + n) % QUEUE_SIZE;
        if(r < nextR){
            memcpy(&queue[r], src, n);
        }
        else{
            half = QUEUE_SIZE - r;
            memcpy(&queue[r], src, half);
            memcpy(queue, &src[half], n-half);
        }
        
        r = nextR;
    } 
    else {
        return;
    }
}

int pop(Data_t* dest, int n){
    if(n <= len){
        len -= n;
        empty += n;
        nextF = (f + n) % QUEUE_SIZE;
        if(nextF >= f){
            memcpy((void*)dest, (void*)&queue[f], n);
        }
        else{
            half = QUEUE_SIZE - f;
            memcpy((void*)dest, (void*)&queue[f], half);
            memcpy((void*)&dest[half], (void*)queue, n-half);
        }

        f = nextF;

        return n;
    }
    else{
        //elements < n
        return 0;
    }
}

int pop(Data_t* dest){
    if(8 <= len){
        len -= 8;
        empty += 8;
        nextF = (f + 8) % QUEUE_SIZE;
        if(nextF >= f){
            memcpy((void*)dest, (void*)&queue[f], 8);
        }
        else{
            half = QUEUE_SIZE - f;
            memcpy((void*)dest, (void*)&queue[f], half);
            memcpy((void*)&dest[half], (void*)queue, 8-half);
        }

        f = nextF;

        return 8;
    }
    else{
        return 0;
        //elements < n
    }
}