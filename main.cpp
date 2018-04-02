#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

#include "queue.h"
#include "serial.h"
#include "util.h"

Data_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int npop = 0;
Data_t buf[255];
int fd, wf;
pthread_mutex_t queMtx = PTHREAD_MUTEX_INITIALIZER;

#pragma pack(push, 1)
typedef union{
    uint8_t raw[8];
    struct {
        uint16_t header;
        uint16_t emg0;
        uint16_t emg1;
        uint16_t enc;
    } p;
} DataSet;
#pragma pack(pop)

DataSet rawData;
uint16_t preEnc = 0;

int main(int argc, char* argv[]){

    wf = open("./data.txt", O_WRONLY | O_TRUNC);
    if( wf == -1){
        perror("open_port: Unable to open data.txt\n");
    }

    initSerial(&fd);

    puts("main thread create");
    char ch = 'r';
    write(fd, &ch, 1);
    int cnt = 0;

    int fileDataDescriptor = -1;
    
    
    char fileName[] = {'.', '/', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '.', 't', 'x', 't', '\0'};
    
    time2int(&fileName[2]);
    fileDataDescriptor = open(fileName, O_WRONLY | O_CREAT);
    
    while(1){

        npop = pop(data);
        if( npop == 8 ){
            write(fileDataDescriptor, data, 8);
            std::copy(data, data+8, rawData.raw);
            if(cnt++ % 10 == 0){
                printf("%d %d %d %d\n", cnt, rawData.p.emg0, rawData.p.emg1, rawData.p.enc);
                preEnc = rawData.p.enc;
            }

            if(preEnc > rawData.p.enc && rawData.p.enc == 0  ){
                close(fileDataDescriptor);
                time2int(&fileName[2]);
                fileDataDescriptor = open(fileName, O_WRONLY | O_CREAT);
            }
        }

        sleep(0);
    }

    deInitSerial(&fd);
    close(fileDataDescriptor);

    return 0;
}
