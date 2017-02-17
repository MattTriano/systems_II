#include <stdlib.h>
#include <stdio.h>

int main ()
{
    int* iPtr;

    iPtr      = (int*)malloc(sizeof(int));
    *(iPtr-1) = 14;
    printf("iPtr = %p, *iPtr = %d\n", iPtr, *iPtr);

    free(iPtr);

    return(EXIT_SUCCESS);
}
