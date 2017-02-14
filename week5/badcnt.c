#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

unsigned int cnt = 0; /* shared */
unsigned int NUM_ITERS;

/* thread routine */
void *count(void *arg) {
    int i;
    for (i = 0; i < NUM_ITERS; i++)
        cnt++;
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t tid1, tid2;

    if ( (argc >= 2) && isdigit(*argv[1]) )
        NUM_ITERS = atoi(argv[1]);
    else {
        const int LINE_SIZE = 16;
        char line[LINE_SIZE];

        do  {
 	    printf("How many iterations shall each thread do? ");
     	    fgets(line, LINE_SIZE, stdin);
            } while ( !isdigit(line[0]) );

        NUM_ITERS = atoi(line);
       }

    pthread_create(&tid1, NULL, count, NULL);
    pthread_create(&tid2, NULL, count, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
