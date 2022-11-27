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
typedef struct Pair {
    int voc;
    int comp;
    sem_t match;
    sem_t finish;
    struct Pair *next;
} Pair;

typedef struct PairList {
    int size;
    Pair *head;
    Pair *tail;
} PairList;

int maxWanderTime;
int maxSoundRoomUsageTime;

sem_t mutex;
sem_t list_mutex;

PairList *pList;

PairList * createPairList();
Pair * addPairToList(PairList *pl);
Pair * createPair();

Pair * findSearchingVoc(int comp);
Pair * findSearchingComp(int voc);

void vocalist(int i);
void composer(int i);

int main(int argc, char *argv[]) {
    // Initialize command line arguments to variables
    char *delayOption = argv[1];
    int vocalists = atoi(argv[2]);
    int composers = atoi(argv[3]);
    int availableRooms = atoi(argv[4]);

    // Creates the blocking logic for available threads
    sem_init(&mutex, 0, availableRooms);
    sem_init(&list_mutex, 0, 1);

    sem_wait(&list_mutex);
    pList = createPairList();
    sem_post(&list_mutex);

    // threads for vocalists and composers
    pthread_t voc_id[vocalists];
    pthread_t comp_id[composers];

    // Checks argument to confirm input is valid
    if (argc < 5) {
        puts("Invalid parameters");
        return EXIT_FAILURE;
    }
        // If valid parameters and correct string, run the "-randomdelay" option
        // argv[5] is the maximum amount of time (in seconds) a vocalist and composer can wander and look for each other
        // argv[6] is the maximum amount of time (in seconds) a pair can use a room for
    else if (argc == 7 && !strcmp(argv[1], "-randomdelay")) {
        maxWanderTime = atoi(argv[5]);
        maxSoundRoomUsageTime = atoi(argv[6]);
    }
        // If valid parameters and correct string, run the "-nodelay" option
        // No wait occurs in this block
    else if (argc == 5 && !strcmp(argv[1], "-nodelay")) {

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

    // TODO handle finishing threads / joining
    // Waits for all threads to finish executing
    for (int i = 0; i < vocalists; i++)
        pthread_join(voc_id[i], NULL);

    for (int i = 0; i < composers; i++)
        pthread_join(comp_id[i], NULL);

    sem_wait(&list_mutex);
    freePairList(pList);
    sem_post(&list_mutex);

    return 0;
}

// executes tasks
void vocalist(int i) {
    // if maxwandering != 0, then sleep
    printf("Vocalist %d: I am wandering...\n", i);
    if(maxWanderTime != 0){
        //TODO wander for random amount of time
    }

    printf("Vocalist %d: I am ready to make music...\n", i);

    Pair *p;

    if ((p = findSearchingComp(i)) != NULL){
        //add self to pair with composer
        //let matching composer know they have been matched via semaphore

        // wait for finish
        sem_wait(&p->finish);

        //TODO handle removing pair from PairList
    }else{
        //create a new pair
        sem_wait(&list_mutex);

        p = addPairToList(pList);

        if (p == NULL){
            printf("ERR_ Could Not Create New Pair!\n");
        }

        p->voc = i;

        sem_post(&list_mutex);

        //wait for a match
        sem_wait(&p->match);

        printf("Vocalist %d and Composer %d found a sound proof room and are making music\n", p->voc, p->comp);

        // find a room
        sem_wait(&mutex);

        if(maxSoundRoomUsageTime != 0){
            // TODO wait in room for a random time
        }

        // release room
        sem_post(&mutex);

        sem_post(&p->finish);
    }

    printf("Vocalist %d: I am leaving... Bye\n", i);

    // Returns to corresponding pthread_join issued in main()
    pthread_exit(0);
}

void composer(int i) {

    // if maxwandering != 0, then sleep
    printf("Composer %d: I am wandering...\n", i);
    if(maxWanderTime != 0){
        //TODO wander for random amount of time
    }

    printf("Composer %d: I am ready to make music...\n", i);

    Pair *p;

    if ((p = findSearchingVoc(i)) != NULL){
        //add self to pair with composer
        //let matching composer know they have been matched via semaphore

        // wait for finish
        sem_wait(&p->finish);

        //TODO handle removing pair from PairList
    }else{
        //create a new pair
        sem_wait(&list_mutex);

        p = addPairToList(pList);

        if (p == NULL){
            printf("ERR_ Could Not Create New Pair!\n");
        }

        p->comp = i;

        sem_post(&list_mutex);

        //wait for a match
        sem_wait(&p->match);

        printf("Vocalist %d and Composer %d found a sound proof room and are making music\n", p->voc, p->comp);

        // find a room
        sem_wait(&mutex);

        if(maxSoundRoomUsageTime != 0){
            //TODO wait in room for a random time
        }

        // release room
        sem_post(&mutex);

        sem_post(&p->finish);
    }

    printf("Composer %d: I am leaving... Bye\n", i);

    // Returns to corresponding pthread_join issued in main()
    pthread_exit(0);
}

PairList * createPairList(){
    PairList *pl;
    pl = malloc(sizeof(PairList));

    if(pl == NULL){
        return pl;
    }

    pl->size = 0;
    pl->head = NULL;
    pl->tail = NULL;

    return pl;
}

void freePairList(PairList *pl){
    if(pl == NULL){
        return;
    }

    Pair *p = pl->head;
    while(p != NULL){
        Pair *prevP = p;
        p = prevP->next;
        free(prevP);
    }
    free(pl);
}

Pair * addPairToList(PairList *pl){
    if(pl == NULL){
        return NULL;
    }

    Pair *p = createPair();

    if(p == NULL){
        return p;
    }

    if(pl->size == 0){
        pl->head = p;
        pl->tail = p;
        pl->size = 1;
    }else{
        pl->tail->next = p;
        pl->tail = p;
        pl->size++;
    }

    return p;
}

Pair * findSearchingVoc(int comp) {
    if (pList->size == 0) {
        return NULL;
    }

    //loop through and check for any vocalist that needs a composer
    Pair *p = pList->head;
    if (p == NULL) {
        return NULL;
    }

    while(p != NULL){

        // following criteria for a vocalist looking for a composer
        if(p->voc != -1 && p->comp == -1){
            sem_wait(&list_mutex);
            //found a vocalist looking for composer, and matching pair made
            p->comp = comp;
            sem_post(&p->match);
            sem_post(&list_mutex);
            return p;
        }

        p = p->next;
    }

    return NULL;
}

Pair * findSearchingComp(int voc) {
    if (pList->size == 0) {
        return NULL;
    }

    Pair *p = pList->head;
    if (p == NULL) {
        return NULL;
    }

    while(p != NULL){
        if(p->comp != -1 && p->voc == -1){
            sem_wait(&list_mutex);
            p->voc = voc;
            sem_post(&p->match);
            sem_post(&list_mutex);
            return p;
        }

        p = p->next;
    }

    return NULL;
}

Pair * createPair(){
    Pair *p;
    p = malloc(sizeof(Pair));

    if(p == NULL){
        return p;
    }

    p->voc = -1;
    p->comp = -1;
    sem_init(&p->match, 0, 1);
    sem_wait(&p->match);
    sem_init(&p->finish, 0, 1);
    sem_wait(&p->finish);
    p->next = NULL;

    return p;
}



