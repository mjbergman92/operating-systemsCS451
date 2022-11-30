/*
    A4 Assignment by Malachi Bergman and Koal Marcione

    Simulate a process making a succession of logical address requests to the MMU
    The MMU then must determine if the page is in RAM. 
    If not, remove using FIFO or LRU and add desired page from disk.
    This is called a page fault. Count these for each algorithm.
    
*/

int main(){

    int page_table[256];
    int ram[32];

    for(int i = 0; i < 256; i++){
        page_table[i] = -1;
    }

    for(int i = 0; i < 32; i++){
        ram[i] = -1;
    }



    return 0;
}