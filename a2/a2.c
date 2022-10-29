#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

void main(int argc, char **argv){
    int quantum = atoi(argv[2]);
    char *inputFilename = argv[1];

    printf("Quantum: %d\n", quantum);
    printf("Input File: %s\n", inputFilename);

    FILE *fp = fopen(inputFilename, "r");
    char *input = malloc(40);
    fgets(input, 35, fp);

    printf("File Contents: %s\n", input);

    free(input);
}