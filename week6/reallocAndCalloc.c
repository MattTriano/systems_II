#include <stdlib.h>
#include <stdio.h>
#define NUM_ELE 4

int  main ()
{
    int* 	iPtr;
    int*  	iPtr2;
    int 	i;

    iPtr 	= (int*)calloc(NUM_ELE, sizeof(int));
    iPtr2 	= (int*)calloc(NUM_ELE, sizeof(int));

    for (i = 0; i < NUM_ELE; i++)
    {
        iPtr[i] = i*10;
    }

    printf("iPtr: \n");
    for (i = 0; i < NUM_ELE; i++)
        printf("%3d is at %p\n", *(iPtr+i), (iPtr+i));

    printf("iPtr2:\n");
    for (i = 0; i < NUM_ELE; i++)
        printf("%3d is at %p\n", *(iPtr2+i), (iPtr2+i));

    printf("Uh-of, not enough space!\n");
    iPtr = (int*)realloc(iPtr, 4*NUM_ELE*sizeof(int));

    for (i = 0; i < 4*NUM_ELE; i++)
        printf("%3d is at %p\n", *(iPtr+i), (iPtr+i));

    free(iPtr2);
    free(iPtr);
    return(EXIT_SUCCESS);
}


