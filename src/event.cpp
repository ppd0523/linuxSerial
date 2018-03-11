#include <fcntl.h>
#include <error.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <linux/input.h>
#include <termios.h>

#include "event.h"

struct termios term;
struct sigaction sigact;
struct input_event evt;
const char* val[3] = {
    "RELEASED",
    "PRESSED",
    "REPEATED"
};
ssize_t n;
int kd;

void signal_handler_IO(int status){
    n = read(kd, &evt, sizeof(input_event));
    if(evt.type == EV_KEY){
        switch(evt.code){
            case KEY_R:
                puts("input R");

                break;
            case KEY_Q:
                puts("input Q");
                
                break;
        }
    }
}

void initKeyEvent(int fd){
    fd = open("/dev/input/by-id/usb-JARGY_MK_Sharing_+_FC_C800C800C800C800-if02-event-kbd", O_RDONLY | O_NOCTTY | O_NDELAY);
    if( fd == -1){
        perror("/dev/input/");
    }
    kd = fd;
    printf("Key interrupt On\n");
    
    sigact.sa_handler = signal_handler_IO;
    sigact.sa_flags = 0;
    sigact.sa_restorer = NULL;
    sigaction(SIGIO, &sigact, NULL);
    
    fcntl(fd, F_SETFL, FNDELAY);
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, O_ASYNC);

}

void deInitKeyEvent(int* fd);