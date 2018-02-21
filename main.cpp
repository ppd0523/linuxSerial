#include <stdio.h>


#include <unistd.h>
#include <fcntl.h>



#include "queue.h"
#include "serial.h"

int connected;
char buf[255];
ssize_t n;

int fd, wf;

void signal_handler_IO(int status){

    n = read(fd, buf, 8);
    write(wf, buf, n);
    
}

int main(int argc, char* argv[]){
    initSerial(&fd);

    wf = open("./data.txt", O_WRONLY | O_TRUNC);
    if( wf == -1){
        perror("open_port: Unable to open data.txt\n");
    }
    connected = 1;

    Data_t b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    push(b, 7);
    pop(b, 5);
    push(b, 7);
    push(b, 5);

    while(connected == 1){
        
    }

    deInitSerial(&fd);
    return 0;
}

static int cnt = 0;

