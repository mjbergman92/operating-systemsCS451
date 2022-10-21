struct Process {
	char *pid;
	int level;
};

#ifndef PROCESS_H_
#define PROCESS_H_

struct Process* newProcess(char *pid, int level);

#endif