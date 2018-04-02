#include <time.h>

#include "util.h"

int power(int n){
    int r = 1;
    for(int i=0; i<n; ++i)
        r *= 10;

    return r;
}

void time2int(char* buffer){
    
    int unixTime = (int)time(NULL);

    int digit = 1;
    for(int i=0; i<9; ++i){
        digit = power(9-i);
        buffer[i] = '0' + (unixTime / digit);
        unixTime = unixTime % digit;
    }
    buffer[9] = '0' + unixTime;
}

// #include <stdio.h>


// int main(){
//     int t = (int)time(NULL);
//     char buf[11];
//     buf[10] = '\0';
//     time2int(buf);

//     printf("%s", buf);
    
//     return 0;
// }