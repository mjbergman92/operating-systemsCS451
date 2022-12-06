/*
    A4 Assignment by Malachi Bergman and Koal Marcione

    Simulate a process making a succession of logical address requests to the MMU
    The MMU then must determine if the page is in RAM.
    If not, remove using FIFO or LRU and add desired page from disk.
    This is called a page fault. Count these for each algorithm.

*/

#include <stdio.h>

int main(int argc, char **argv)
{

    /*
     *   With 8-bit page numbers, there can be 256 different pages
     *
     *   With a total of 2^13 bits of RAM, and each page of data
     *   having 256 (2^8) bits, that leaves 2^5 number of frames
     *   on ram, so 32 frames
     */

    // Initialize variables for FIFO

    int fifo_page_table[256], fifo_ram[32];
    int fifo_page_faults = 0;
    int fifo_frame = 0;

    for (int i = 0; i < 256; i++)
        fifo_page_table[i] = -1;    // intialize all to invalid

    for (int i = 0; i < 32; i++)
        fifo_ram[i] = -1;           // initialize all to less than 0, so -1

    // Initialize variables for LRU

    int lru_page_table[256], lru_ram[32];
    int lru_page_faults = 0;
    int lru[32];

    for (int i = 0; i < 256; i++)
        lru_page_table[i] = -1;     // intialize all to invalid

    for (int i = 0; i < 32; i++)
        lru_ram[i] = -1;            // initialize all to less than 0, so -1

    for (int i = 0; i < 32; i++)
        lru[i] = i;                 // initialize all to the index of ram

    // Initialize the file pointers

    FILE *fp = fopen(argv[1], "r");
    FILE *fifo_fp = fopen("FIFO_PhysicalAddresses.txt", "w");
    FILE *lru_fp = fopen("LRU_PhysicalAddresses.txt", "w");

    int logAdrs, frame, count = 0;
    while (fscanf(fp, "%d", &logAdrs) == 1)
    {
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

        // Using FIFO Algorithm

        /* INVALID - PAGE FAULT */
        if ((frame = fifo_page_table[page]) == -1)
        {
            fifo_page_faults++;

            if (fifo_ram[fifo_frame] != -1)
                fifo_page_table[fifo_ram[fifo_frame]] = -1; // invalidate page being replaced in ram
            fifo_ram[fifo_frame] = page;                    // load page into ram
            fifo_page_table[page] = fifo_frame;             // set associate frame for page in page table

            int physAdrs = fifo_frame * 256 + offset; // remember, multiple by 256 is like left shift 8 in binary
            fprintf(fifo_fp, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\n", count, physAdrs, page, fifo_frame, offset);

            /*
             *   next frame (which is the oldest / the first in),
             *   cycling back to 0 after all 32 frames in ram
             */
            fifo_frame = (fifo_frame + 1) % 32;
        }
        /* VALID */
        else
        {
            int physAdrs = frame * 256 + offset; // remember, multiple by 256 is like left shift 8 in binary
            fprintf(fifo_fp, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\tNO_FAULT\n", count, physAdrs, page, frame, offset);
        }

        // Using FIFO Algorithm

        /* INVALID - PAGE FAULT */
        if ((frame = lru_page_table[page]) == -1)
        {
            lru_page_faults++;
            int least_recently_used = lru[0];

            if (lru_ram[least_recently_used] != -1)
                lru_page_table[lru_ram[least_recently_used]] = -1; // invalidate page being replaced in ram
            lru_ram[least_recently_used] = page;                   // load page into ram
            lru_page_table[page] = least_recently_used;            // set associate frame for page in page table

            int physAdrs = least_recently_used * 256 + offset; // remember, multiple by 256 is like left shift 8 in binary
            fprintf(lru_fp, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\n", count, physAdrs, page, least_recently_used, offset);

            /*
             *   shift everything else to be less recently used
             *   and place "least_recently_used" as most recently used
             */

            for (int i = 0; i < 32 - 1; i++)
                lru[i] = lru[i + 1];

            lru[31] = least_recently_used;
        }
        /* VALID */
        else
        {
            int physAdrs = frame * 256 + offset; // remember, multiple by 256 is like left shift 8 in binary
            fprintf(lru_fp, "%d:\t%d\tPage:%d\tFrame:%d\tOffset:%d\tNO_FAULT\n", count, physAdrs, page, frame, offset);

            /*
             *   find the index in the lru "stack"
             *   of the frame
             */

            int index;

            for (index = 0; index < 32; index++)
                if (lru[index] == frame) break;

            /*
             *   shift everything "more recently used" to be less
             *   recently used than the most recently used frame
             */

            for (int i = index; i < 32 - 1; i++)
                lru[i] = lru[i + 1];

            lru[31] = frame;
        }
    }

    printf("The number of page faults for FIFO was <%d>\n", fifo_page_faults);
    printf("The number of page faults for LRU was <%d>\n", lru_page_faults);

    fclose(fifo_fp);
    fclose(lru_fp);

    return 0;
}