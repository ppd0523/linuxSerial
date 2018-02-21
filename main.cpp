#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <errno.h>
#include <termios.h>

#include <time.h>

#include "queue.h"

void signal_handler_IO(int status);

int fd, wf;
int connected;
struct termios termAttr;
struct sigaction saio;

struct timespec t;
char buf[255];
ssize_t n;

int main(int argc, char* argv[]){
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if( fd == -1){
        perror("open_port: Unable to open /dev/ttyUSB0\n");
    }

    wf = open("./data.txt", O_WRONLY | O_TRUNC);
    if( wf == -1){
        perror("open_port: Unable to open data.txt\n");
    }

    printf("hello world\n");
    
    saio.sa_handler = signal_handler_IO;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio, NULL);
    
    fcntl(fd, F_SETFL, FNDELAY);
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, O_ASYNC);
    
    tcgetattr(fd, &termAttr);
    cfsetispeed(&termAttr, B115200);
    cfsetospeed(&termAttr, B115200);
    
    termAttr.c_cflag &= ~PARENB;
    termAttr.c_cflag &= ~CSTOPB;
    termAttr.c_cflag &= ~CSIZE;
    termAttr.c_cflag |= CS8;
    termAttr.c_cflag |= (CLOCAL | CREAD);
    termAttr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    termAttr.c_iflag &= ~(IXON | IXOFF | IXANY);
    termAttr.c_oflag &= ~OPOST;
    
    tcsetattr(fd, TCSANOW, &termAttr);

    connected = 1;

    Data_t b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    push(b, 7);
    pop(b, 5);
    push(b, 7);
    push(b, 5);

    while(connected == 1){
        
    }

    close(fd);
    close(wf);
    return 0;
}

static int cnt = 0;

void signal_handler_IO(int status){
    if(cnt ++ > 80){
        cnt = 0;
        printf("%16d %x%x%x%x%x%x%x%x\n", cnt, buf[0], buf[1],buf[2], buf[3],buf[4],buf[5],buf[6],buf[7]);

    }
    n = read(fd, buf, 8);
    write(wf, buf, n);
    
}