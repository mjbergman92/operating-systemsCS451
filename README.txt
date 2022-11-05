INSTRUCTION
In order to run the program, compile the a2.c file and prime.c seperately using:
gcc a2.c pid.c -o a2
gcc prime.c -o prime
To run the program, enter the following:
./a2 input.txt <quantum>
where <quantum> is an integer

Make sure all files are in the same location and you are in the correct directory for running the program. It needs an input.txt file that
contain processes and each burst time. After you run the process go ahead and wait for the results to generate.

An example of the input.txt file is as listed below:
Process ID Burst
0 10
4 10
5 20
6 15
...and so on

Issues: The program is not async safe. 