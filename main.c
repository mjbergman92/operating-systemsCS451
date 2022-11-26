/*
 * Program Created by Malachi Bergman and Koal Marcione
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

/*
 * Program will take in a value which represents the number of "rooms" that can be occupied, number of composers, and number of vocalists
 * The first room will be occupied by the first composer and vocalist pair, and same with the second and so on. This ends when all the vocalists
 * have left. Any time all rooms are full the composers/vocalists will be in a waiting state in order to get in.
 * A composer will decrement room value by 1 when they find a vocalist
 * A composer will then increment a room value by 1 when they and a vocalist leave
 */

sem_t mutex;
sem_t arr_mutex; // For writing to the arrays

// arrays of IDs of vocalists and composers
int *voc;
int *comp;
sem_t *matching_wait;

int main(int argc, char *argv[]) {
    // Initialize command line arguments to variables
    char *delayOption = argv[1];
    int vocalists = atoi(argv[2]);
    int composers = atoi(argv[3]);
    int availableRooms = atoi(argv[4]);
    int maxWanderTime = atoi(argv[5]);
    int maxSoundRoomUsageTime = atoi(argv[6]);

    // allocate and initialize lists to -1

    // threads for vocalists and composers
    pthread_t voc_id[vocalists];
    pthread_t comp_id[composers];

    // Creates the blocking logic for available threads

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


    // Creates thread count equivalent to int of vocalists
    for (int i = 0; i < vocalists; i++)
        pthread_create(&voc_id [i], NULL, vocalist, (void *) i);

    // Creates thread count equivalent to int of composers
    for (int i = 0; i < composers; i++)
        pthread_create(&comp_id [i], NULL, composer, (void *) i);

    // Waits for all threads to finish executing
    for (int i = 0; i < availableRooms; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}

// executes tasks
void vocalist(int i) {
    // if maxwandering != 0, then sleep

    // Returns to corresponding pthread_join issued in main()
    pthread_exit(0);
}

void composer(int i) {
    // The occupation of a room with a vocalist and composer goes here

    // Returns to corresponding pthread_join issued in main()
    pthread_exit(0);
}