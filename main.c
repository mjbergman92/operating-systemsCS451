/*
 * Program Created by Malachai Bergman and Koal Marcione
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include "MakeMusic.c"

/*
 * Program will take in a value which represents the number of "rooms" that can be occupied, number of composers, and number of vocalists
 * The first room will be occupied by the first composer and vocalist pair, and same with the second and so on. This ends when all the vocalists
 * have left. Any time all rooms are full the composers/vocalists will be in a waiting state in order to get in.
 * A composer will decrement room value by 1 when they find a vocalist
 * A composer will then increment a room value by 1 when they and a vocalist leave
 */

int availableRooms;
int composers;
int vocalists;
int maxWanderTime;
int maxSoundRoomUsageTime;
char delayOption;

int main(int argc, char *argv[]) {
    // Initialize command line arguments to variables
    delayOption = argv[1];
    vocalists = argv[2];
    composers = argv[3];
    availableRooms = argv[4];
    maxWanderTime = argv[5];
    maxSoundRoomUsageTime = argv[6];

    pthread_t thread_id[availableRooms];

    // Creates the blocking logic for available threads
    sem_t mutex;
    sem_init(&mutex, 0, availableRooms);



    // Checks argument to confirm input is valid
    if (argc < 5) {
        puts("Invalid parameters");
        return EXIT_FAILURE;
    }
        // If valid parameters and correct string, run the "-randomdelay" option
        // argv[5] is the maximum amount of time (in seconds) a vocalist and composer can wander and look for each other
        // argv[6] is the maximum amount of time (in seconds) a pair can use a room for
    else if (argc = 7 && argv[1] == "-randomdelay") {

    }
        // If valid parameters and correct string, run the "-nodelay" option
        // No wait occurs in this block
    else if (argc = 5 && argv[1] == "-nodelay") {

    }
    else {
        puts("Invalid parameters");
        return EXIT_FAILURE;
    }


    // Creates thread count equivalent to int of availableRooms
    for (int i = 0; i < availableRooms; i++)
        pthread_create(&thread_id [i], NULL, occupy_room, (void *) i);

    // Waits for all threads to finish executing
    for (int i = 0; i < availableRooms; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}

// executes tasks
void occupy_room(int i) {
    // The occupation of a room with a vocalist and composer goes here

    // Returns to corresponding pthread_join issued in main()
    pthread_exit(0);
}

typedef struct {
    int value;
    struct process *list;
} semaphore;

void wait(semaphore *S) {
    S->value--;
    if (S->value < 0) {
        //add this process to S->list;
        sleep();
    }
}

void signal(semaphore *S) {
    S->value++;
    if (S->value <=0) {
        //remove a process P from S->list;
        wakeup(P);
    }
}

typedef struct {

} Vocalist;

typedef struct {

} Composer;