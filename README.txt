How to run the program
First compile by going to the file location and running the following in command prompt
gcc main.c
./a.out <address file>

Where <address file> is the properly formatted text file, located in the same directory as the main program. The address
file contains only a list of 16-bit unsigned integers in decimal form, seperated by empty space (spaces, tabs, new lines, etc.)
The results will be printed to the two text files that will be created in that location, and to the
command prompt it will print out the number of faults found in the FIFO and LRU methods.

Issues with the program: It doesn't validate the format of the file. The file has to have integer values within
the 16-bit integer range as described by the format