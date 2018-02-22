#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "queue.h"
#include "serial.h"

int connected;
Data_t buf[255];
Data_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
ssize_t n;

int fd, wf;

void signal_handler_IO(int status){

    n = read(fd, buf, 255);
    push(buf, n);
}

int main(int argc, char* argv[]){
    

    wf = open("./data.txt", O_WRONLY | O_TRUNC);
    if( wf == -1){
        perror("open_port: Unable to open data.txt\n");
    }

    connected = 1;
    
    initSerial(&fd);

    while(connected == 1){
        if( pop(data) ){
            write(wf, data, 8);
        }
    
    }

    deInitSerial(&fd);
    close(wf);
    return 0;
}

static int cnt = 0;

