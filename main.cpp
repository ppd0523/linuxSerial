#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <errno.h>
#include <termios.h>

void signal_handler_IO(int status);

int n;
int fd;
int connected;
struct termios termAttr;
struct sigaction saio;


int main(int argc, char* argv[]){
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if( fd == -1){
        perror("open_port: Unable to open /dev/ttyUSB0\n");
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

    while(connected == 1){

    }

    close(fd);
    
    return 0;
}

void signal_handler_IO(int status){
    printf("receive data from UART.\n");
}