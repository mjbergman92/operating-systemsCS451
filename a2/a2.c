//
// Created by malachi.bergman and koal.marcione on 10/28/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include "pid.h"

#define LINE_MAX 40
/*
 initiating global  variables
*/
Queue *queue = NULL;
PID *pid = NULL;
int quantum;
int loops = 0;
int doPrint = 0;
int prevPID = -1;

void sigalrm(int signal){
    // suspend or terminate currently running process, if there is one running
    prevPID = -1;
    if(pid != NULL){
        prevPID = pid->namePID;
        pid->burst -= quantum;
        if(pid->burst <= 0){
            kill(pid->pid, SIGTERM);
            free(pid);
        }else{
            kill(pid->pid, SIGTSTP);
            enqueuePID(queue, pid);
        }
    }

    pid = dequeuePID(queue);

    //check if all processes have left the queue
    if(pid == NULL){
        freeQueue(queue);
        exit(0);
    }

    // start or resume next process
    if(pid->pid == -1){
        int p = fork();
        if(p == 0){
            char pid_str[6];
            int __pid = pid->namePID;
            int i;
            for(i = 0; i < 6 - 1 && __pid > 0; i++){
                int digit = __pid % 10;
                __pid /= 10;
                pid_str[i] = digit + '0';
            }
            pid_str[i] = '\0';
            if(execl("./prime/cmake-build-debug/prime", "prime", pid_str, NULL) == -1){
                exit(-1);
            }
        }
        pid->pid = p;
    }else{
        kill(pid->pid, SIGCONT);
    }

    doPrint = 1;
    loops++;
}

void setupTimer(){
    struct itimerval timer;
    /* Install timer_handler as the signal handler for SIGALRM. */
    /* The timer goes off 10 seconds after installation of the timer*/
    timer.it_value.tv_sec = quantum;
    timer.it_value.tv_usec =0;
    /* ... and every 10 seconds after that. */
    timer.it_interval.tv_sec = quantum;
    timer.it_interval.tv_usec =0;
    /* Start a real timer. It counts down whenever this process is executing. */
    setitimer (ITIMER_REAL, &timer, NULL);
}

void setupAlarm(){
    struct sigaction sa;
    /* Install timer_handler as the signal handler for SIGALRM. */
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &sigalrm;
    sigaction(SIGALRM, &sa, NULL);
}

void main(int argc, char **argv){
    char *inputFilename = argv[1];
    quantum = atoi(argv[2]);

    //printf("Quantum: %d\n", quantum);
    //printf("Input File: %s\n", inputFilename);

    FILE *fp = fopen(inputFilename, "r");

    //skip the header line
    char input[LINE_MAX];
    fgets(input, LINE_MAX, fp);
    //printf("Skipped: %s\n", input);

    // parse input file into queue
    queue = createQueue();
    int namePID, burst;
    while(fscanf(fp, "%d%d", &namePID, &burst) == 2){
        PID *_pid = createPID(namePID, burst);
        enqueuePID(queue, _pid);
    }

    fclose(fp);

    // queueToString(queue);

    setupTimer();
    setupAlarm();
/*
    Loop that controls main program and creation of children processes
 */
    while(1) {
        if(doPrint){
            printf("\nScheduler: Time Now: %d second\n", loops * quantum);

            if(prevPID == -1) {
                //starting process when pid == NULL
                printf( "Scheduling to Process %d (Pid %d) for the time slice of %d seconds.\n", pid->namePID, pid->pid, quantum);
            }else{
                //for processes with pid != NULL
                printf("Suspending Process %d and scheduling Process %d (Pid %d) for the time\n"
                                       "slice of %d seconds.\n", prevPID, pid->namePID, pid->pid, quantum);
            }

            doPrint = 0;
        }
    };
}