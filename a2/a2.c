#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pid.h"

#define LINE_MAX 40

void main(int argc, char **argv){
    char *inputFilename = argv[1];
    int quantum = atoi(argv[2]);

    printf("Quantum: %d\n", quantum);
    printf("Input File: %s\n", inputFilename);

    FILE *fp = fopen(inputFilename, "r");

    //skip the header line
    char input[LINE_MAX];
    fgets(input, LINE_MAX, fp);
    printf("Skipped: %s\n", input);

    Queue *queue = createQueue();

    int namePID, burst;
    while(fscanf(fp, "%d%d", &namePID, &burst) == 2){
        PID *pid = createPID(namePID, burst);
        enqueuePID(queue, pid);
    }

    queueToString(queue);

    freeQueue(queue);
}