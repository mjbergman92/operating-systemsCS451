//
// Created by malachi.bergman on 10/28/2022.
//

#include <signal.h>

void sigtstp(int signal){

}
void sigcont(int signal){

}
void sigterm(int signal){

}

void main(int argc, char **argv){
    signal(SIGTSTP, sigtstp);
    signal(SIGCONT, sigcont);
    signal(SIGTERM, sigterm);

}
