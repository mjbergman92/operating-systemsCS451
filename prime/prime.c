//
// Created by malachi.bergman on 10/28/2022.
//

#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

long unsigned int prime = 0;
int namePID, pid;
int printFlag = 0;

void sigtstp(int signal){
    printFlag = 1;
}
void sigcont(int signal){
    printFlag = 2;
}
void sigterm(int signal){
    printFlag = 3;
}

long unsigned int get10DigitRandom(){
    srand(time(NULL));

    long unsigned int output = 0;

    for(int i = 0; i < 10; i++){
        int r = rand() % 10;
        output = output * 10 + r;
    }

    return output;
}

int checkPrime(long unsigned int number){
    for(long unsigned int i = 2; i < number; i++){
        if(number % i == 0){
            return 0;
        }
    }
    return 1;
}

void setupSignals(){
    struct sigaction sa1, sa2, sa3;
    /* Install timer_handler as the signal handler for SIGALRM. */
    memset (&sa1, 0, sizeof (sa1));
    sa1.sa_flags = SA_RESTART;
    sa1.sa_handler = &sigtstp;
    sigaction(SIGTSTP, &sa1, NULL);

    /* Install timer_handler as the signal handler for SIGALRM. */
    memset (&sa2, 0, sizeof (sa2));
    sa2.sa_flags = SA_RESTART;
    sa2.sa_handler = &sigcont;
    sigaction(SIGCONT, &sa2, NULL);

    /* Install timer_handler as the signal handler for SIGALRM. */
    memset (&sa3, 0, sizeof (sa3));
    sa3.sa_flags = SA_RESTART;
    sa3.sa_handler = &sigterm;
    sigaction(SIGTERM, &sa3, NULL);
}

void main(int argc, char **argv){
    setupSignals();

    long unsigned int number = get10DigitRandom();

    namePID = atoi(argv[1]);
    pid = getpid();

    //initial message when prime process started
    printf("Process %d: my PID is %d: I just got started. I am starting with the\n"
           "number %lu to find the next prime number.\n", namePID, pid, number);

    while(1){
        if(checkPrime(number)){
            prime = number;
        }
        number++;

        switch(printFlag){
            case 1:
                printf("Process %d: my PID is %d: I am about to be suspended... Highest prime\n"
                    "number I found is %lu.\n", namePID, pid, prime);
                break;
            case 2:
                printf("Process %d: my PID is %d: I just got resumed.\n", namePID, pid);
                break;
            case 3:
                printf("Process %d: my PID is %d: I completed my task and I am exiting.\n"
                    "Highest prime number I found is %lu.\n", namePID, pid, prime);
                break;
            default:
                break;
        }

        printFlag = 0;
    }
}




