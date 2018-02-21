#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/signal.h>
#include <stdio.h>
#include <unistd.h>


#include "serial.h"


struct termios termAttr;
struct sigaction saio;

extern void signal_handler_IO(int status);

void initSerial(int* fd){
    *fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if( *fd == -1){
        perror("open_port: Unable to open /dev/ttyUSB0\n");
    }

    saio.sa_handler = signal_handler_IO;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio, NULL);
    
    fcntl(*fd, F_SETFL, FNDELAY);
    fcntl(*fd, F_SETOWN, getpid());
    fcntl(*fd, F_SETFL, O_ASYNC);
    
    tcgetattr(*fd, &termAttr);
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
    
    tcsetattr(*fd, TCSANOW, &termAttr);
}

void deInitSerial(int* fd){
    close(*fd);

}