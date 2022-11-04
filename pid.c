//
// Created by malachi.bergman on 10/29/2022.
//
#include <stdlib.h>
#include "pid.h"

Queue * createQueue(){
    Queue *q = malloc(sizeof(Queue));

    if(q == NULL){
        return q;
    }

    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

PID * createPID(int namePID, int burst){
    PID *pid = malloc(sizeof(PID));

    if(pid == NULL){
        return pid;
    }

    pid->namePID = namePID;
    pid->pid = -1;
    pid->burst = burst;
    pid->next = NULL;

    return pid;
}

int enqueuePID(Queue *q, PID *pid){
    if(q == NULL){
        return -1;
    }

    if(q->size == 0){
        q->head = pid;
        q->tail = pid;
        q->size++;
        return q->size;
    }

    q->tail->next = pid;
    q->tail = pid;
    q->size++;
    return q->size;
}

PID * dequeuePID(Queue *q){
    if(q == NULL){
        return NULL;
    }

    if(q->size == 0){
        return NULL;
    }

    PID *pid = q->head;

    if(q->size == 1){
        q->head = NULL;
        q->tail = NULL;
        q->size--;
        return pid;
    }

    q->head = pid->next;
    q->size--;
    return pid;
}

int freeQueue(Queue *q){
    if(q == NULL){
        return 0;
    }

    PID *pid;

    while((pid = dequeuePID(q)) != NULL){
        free(pid);
    }

    free(q);

    return 0;
}

void queueToString(Queue *q){
    if(q == NULL){
        return;
    }

    printf("Queue Contents:\n");

    PID *pid = q->head;

    while(pid != NULL){
        printf("PID %d: \n\tAct. PID#%d\n\tRem. Burst:%d\n", pid->namePID, pid->pid, pid->burst);
        pid = pid->next;
    }
}
