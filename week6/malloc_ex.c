#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int* iPtr;
  
    printf("sizeof (int) = %d\n", sizeof(int));
    iPtr = (int*)malloc(sizeof(int));
    *iPtr = 14;
    printf("iPtr = %p, *iPtr = %d\n", iPtr, *iPtr);
    free(iPtr);
    printf("iPtr = %p\n", iPtr);
    return(EXIT_SUCCESS);
}
