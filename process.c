#include <stdlib.h>
#include "process.h"

struct Process* newProcess(char *pid, int level){
	struct Process *p;
	p = malloc(sizeof(struct Process));

	if(p == NULL){
		return p;
	}

	p->pid = pid;
	p->level = level;

	return p;
}