/*
    A4 Assignment by Malachi Bergman and Koal Marcione

    Simulate a process making a succession of logical address requests to the MMU
    The MMU then must determine if the page is in RAM. 
    If not, remove using FIFO or LRU and add desired page from disk.
    This is called a page fault. Count these for each algorithm.
    
*/

#include <stdio.h>

int main(int argc, char **argv){

    /*
    *   With 8-bit page numbers, there can be 256 different pages
    *   
    *   With a total of 2^13 bits of RAM, and each page of data
    *   having 256 (2^8) bits, that leaves 2^5 number of frames 
    *   on ram, so 32 frames
    */
    int page_table[256];
    int ram[32];

    int pageFaults = 0;

    //int page_history[1000]; //for LRU
    int fifo_frame = 0; //for FIFO

    for(int i = 0; i < 256; i++){   //intialize all to invalid
        page_table[i] = -1;
    }

    for(int i = 0; i < 32; i++){    //initialize all to less than 0, so -1. Would work if 0, but for 
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
        /*
        *   In binary, in order to get the page number, because the 
        *   offset is 8-bit, we would do a right shift of 8-bits
        *   to calculate the page number. Every right shift in binary
        *   is the equivalent of dividing by 2 (conversely, every left shift is
        *   multiplying by 2). Dividing by 2, 8 times, is equivalent to dividing
        *   by 2^8 or 256 once. We can get the page number by dividing the
        *   logical address by 256. 
        *
        *   In binary, in order to get the offset, we make a copy of only the 
        *   8 least significant bits, essentially removing the more significant bits. 
        *   This could be done by subtracting one from the 8 most significant bits
        *   until it equalled zero, although in binary, this is unneccesary. In
        *   decimal form, integer division is essentially subtracting over and over
        *   until another subtraction is not possible. Using division, the number of
        *   subtractions can be done. The remainder after all of the subtracts
        *   can be found using the modulus operator. Subtracting one from the 8
        *   most significant bits is equivalent to subtracting 256 from the decimal
        *   representation. Therefore, we can modulus 256 from the logical
        *   address to determine the offset.
        */
        int page = logAdrs / 256;
        int offset = logAdrs % 256;

        int frame;
        /* INVALID - PAGE FAULT */
        if((frame = page_table[page]) == -1){
            pageFaults++;

            if(ram[fifo_frame] != -1)
                page_table[ram[fifo_frame]] = -1;   //invalidate page being replaced in ram
            ram[fifo_frame] = page;                 //load page into ram
            page_table[page] = fifo_frame;          //set associate frame for page in page table

            int physAdrs = fifo_frame * 256 + offset;   //remember, multiple by 256 is like left shift 8 in binary
            fprintf(outFP, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\n", count, physAdrs, page, fifo_frame, offset);

            /*
            *   next frame (which is the oldest / the first in), 
            *   cycling back to 0 after all 32 frames in ram
            */
            fifo_frame = (fifo_frame + 1) % 32;

        /* VALID */
        }else{
            int physAdrs = frame * 256 + offset;    //remember, multiple by 256 is like left shift 8 in binary
            fprintf(outFP, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\tNO_FAULT\n", count, physAdrs, page, frame, offset);
        }
    }

    printf("The number of page faults for FIFO was <%d>\n", pageFaults);

    return 0;
}