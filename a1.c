#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "process.h"

struct Process* newProcess(char *pid, int level);

void main(int argc, char **argv){
	char *pid = argv[1];

	struct Queue *queue  = newQueue(100);

	enqueue(queue, newProcess(pid, 0));
	struct Process *process = dequeue(queue);
	printf("PID: %s, Level: %d\n", process->pid, process->level);

	/*
	enqueue(queue, pid);
	char * _p = dequeue(queue);
	printf("PID: %s\n", _p);*/

	return;
}