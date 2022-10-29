//
// Created by malachi.bergman on 10/29/2022.
//

#include <stdio.h>

typedef struct PID {
    int namePID;
    int pid;
    int burst;
    struct PID *next;
} PID;

typedef struct Queue{
    int size;
    PID *head;
    PID *tail;
} Queue;

#ifndef A2_PID_H
#define A2_PID_H

Queue * createQueue();

PID * createPID(int namePID, int burst);

int enqueuePID(Queue *q, PID *pid);

PID * dequeuePID(Queue *q);

int freeQueue(Queue *q);

void queueToString(Queue *q);

#endif //A2_PID_H
