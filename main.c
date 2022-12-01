/*
    A4 Assignment by Malachi Bergman and Koal Marcione

    Simulate a process making a succession of logical address requests to the MMU
    The MMU then must determine if the page is in RAM. 
    If not, remove using FIFO or LRU and add desired page from disk.
    This is called a page fault. Count these for each algorithm.
    
*/

#include <stdio.h>

int main(int argc, char **argv){

    int page_table[256];
    int ram[32];

    int pageFaults = 0;

    //int page_history[1000]; //for LRU
    int fifo_frame = 0; //for FIFO

    for(int i = 0; i < 256; i++){
        page_table[i] = -1;
    }

    for(int i = 0; i < 32; i++){
        ram[i] = -1;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *outFP = fopen("FIFO_PhysicalAddresses.txt", "w"); //for FIFO
    //FILE *outFP = fopen("LRU_PhysicalAddresses.txt", "w"); //for LRU


    //Using FIFO Algorithm
    int logAdrs;
    int count = 0;
    while(fscanf(fp, "%d", &logAdrs) == 1){
        count++;
        int page = logAdrs / 256;
        int offset = logAdrs % 256;

        int frame;
        if((frame = page_table[page]) == -1){   //invalid
            pageFaults++;

            page_table[ram[fifo_frame]] = -1;
            ram[fifo_frame] = page;
            page_table[page] = fifo_frame;

            int physAdrs = fifo_frame * 256 + offset;
            fprintf(outFP, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\n", count, physAdrs, page, fifo_frame, offset);

            fifo_frame = (fifo_frame + 1) % 32;    
        }else{                                  //valid
            int physAdrs = frame * 256 + offset;
            fprintf(outFP, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\tNO_FAULT\n", count, physAdrs, page, frame, offset);
        }
    }

    printf("The number of page faults for FIFO was <%d>\n", pageFaults);

    return 0;
}