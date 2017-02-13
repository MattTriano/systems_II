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
    
    printf("Please enter an integer: \n");
    fgets(line, MAX_LINE, stdin);
    entry = (int) strtol(line, NULL, 10);

    switch(id) {
        case 0: 	*iPtr = global0 - global1; break;
        case 1: 	*iPtr = global0 + global1; break;   
    }
    return((void*)ptr);
}

int main ()
{
    int         i;
    const char* msgPtr;
    pthread_t   tid[N];
    int 	index[N];

    printf("Please enter an integer: \n");
    fgets(line, LINE_LEN, stdin);
    entry = (int) strtol(line, NULL, 10);

    for (i = 0; i < N; i++)
    {
 	index[i]= i;
        pthread_create (&tid[i], NULL, thread_routine, (void *)&index[i]); 
    }
 
