#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* naughtyCopy (const char* fromP, size_t n)
{
    if (fromP == NULL || n == 0)
        return(NULL);

    size_t length = strlen(fromP) + 1;

    if (n > length)
        n = length;

    char* toP = (char*)malloc(strlen(fromP)+1);
    char* toReturn = toP;

    for ( ; n > 1  && *fromP != '\0'; n--, fromP++, toP++)
        *toP = *fromP;

    *toP = '\0';
    return(toReturn);
}

int main ()
{
//    char*  	cPtr    = naughtyCopy("Hello guys, how's it going?");
    const  char* toCopy = "Hello class, how are you?";
    int    	 i;

    for (i = 80; i > 0; i--) {
        char* cPtr = naughtyCopy(toCopy, i);

        printf("\"%s\"\n", cPtr);
        free((void*)cPtr);
    }

//    printf("%s\n", cPtr);
//    free(cPtr);
    return(EXIT_SUCCESS);
}
