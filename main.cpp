#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#include "queue.h"
#include "serial.h"

#include <time.h>


Data_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int npop = 0;
Data_t buf[255];
int fd, wf;
pthread_t hThread;
pthread_mutex_t queMtx = PTHREAD_MUTEX_INITIALIZER;

// void* recvThread(void* arg){
//     puts("recv thread create");
//     while(1){
//         pthread_mutex_lock(&queMtx);

//         n = read(fd, buf, 255);
//         push(data, n);
        
//         pthread_mutex_unlock(&queMtx);
//         sleep(0);
//     }
// }

int main(int argc, char* argv[]){

    wf = open("./data.txt", O_WRONLY | O_TRUNC);
    if( wf == -1){
        perror("open_port: Unable to open data.txt\n");
    }

    // pthread_create(&hThread, NULL, recvThread, NULL);
    initSerial(&fd);

    puts("main thread create");
    char ch = 'r';
    write(fd, &ch, 1);
    while(1){
        pthread_mutex_lock(&queMtx);

        npop = pop(data);
        if( npop == 8 ){
            write(wf, data, 8);
        }

        pthread_mutex_unlock(&queMtx);
        sleep(0);
    }
    int status;
    pthread_join(hThread, (void**)&status);
    deInitSerial(&fd);
    close(wf);

    return 0;
}
