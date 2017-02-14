#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define 	LINE_LEN 	16
const int N = 2;

int 	global0;
int 	global1;

void *thread_routine(void *vargp)
{
    int id = 	*(int*)vargp;
    int* iPtr = (int*)malloc(sizeof(int));
    
    switch(id) {
        case 0: 	*iPtr = global0 - global1; break;
        case 1: 	*iPtr = global0 + global1; break;   
    }
    return((void*)iPtr);
}

int main ()
{
    int         i;
    int* 	valuePtr;
    const char* msgPtr;
    pthread_t   tid[N];
    int 	index[N];
    char 	line[LINE_LEN];

    printf("Please enter an integer: ");
    fgets(line, LINE_LEN, stdin);
    global0 = (int) strtol(line, NULL, 10);

    printf("Please enter another integer: ");
    fgets(line, LINE_LEN, stdin);
    global1 = (int) strtol(line, NULL, 10);

    for (i = 0; i < N; i++)
    {
 	index[i]= i;
        pthread_create (&tid[i], NULL, thread_routine, (void *)&index[i]); 
    }

    for ( i = 0; i < N; i++) {
        pthread_join(tid[i], (void**)&valuePtr);

        if (i == 0)
            printf("%d - %d = %d \n", global0, global1, *valuePtr);
        else
            printf("%d + %d = %d \n", global0, global1, *valuePtr);
        free(valuePtr);
    }

    return(EXIT_SUCCESS);
}
 






