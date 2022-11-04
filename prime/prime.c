//
// Created by malachi.bergman and koal.marcione on 10/28/2022.
//

#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

long unsigned int prime = 0;
int namePID, pid;

/*
    Flag for Signaling a stop to the child
 */
void sigtstp(int signal){
    printf("Process %d: my PID is %d: I am about to be suspended...\n", namePID, pid);
    if(prime != 0) {
        printf("Highest prime number I found is %lu.\n", prime);
    }else{
        printf("No prime found yet.\n");
    }

    fflush(stdout);
}
/*
    Flag for continuing an already running child
 */
void sigcont(int signal){
    printf("Process %d: my PID is %d: I just got resumed.\n", namePID, pid);
    fflush(stdout);
}
/*
    Flag for terminating a running child
 */
void sigterm(int signal){
    printf("Process %d: my PID is %d: I completed my task\n", namePID, pid);
    if(prime != 0) {
        printf("and I am exiting. Highest prime number I found is %lu.\n", prime);
    }else{
        printf("and I am exiting. Never found a prime number.\n");
    }
    fflush(stdout);
}

/*
    Generates a random 10 digit number to search for next Prime
 */
long unsigned int get10DigitRandom(){
    srand(time(NULL));

    long unsigned int output = 0;

    for(int i = 0; i < 10; i++){
        int r = rand() % 10;
        output = output * 10 + r;
    }

    return output;
}

/*
    Checks given number to see if it is prime
 */
int checkPrime(long unsigned int number){
    for(long unsigned int i = 2; i < number; i++){
        if(number % i == 0){
            return 0;
        }
    }
    return 1;
}

/*
    Establish signals for Child Process
 */
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
/*
    inefficient prime finding algorithm for random 10 digit or greater number
 */
void main(int argc, char **argv){
    setupSignals();

    long unsigned int number = get10DigitRandom();

    namePID = atoi(argv[1]);
    pid = getpid();

    //initial message when prime process started
    printf("Process %d: my PID is %d: I just got started. I am starting with the\n"
           "number %lu to find the next prime number.\n", namePID, pid, number);

    /*
        Loop that controls running child
     */
    while(1){
        if(checkPrime(number)){
            prime = number;
        }
        number++;

    }
}




