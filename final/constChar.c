#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const 	int	BUFFER_LEN = 32;

int main()
{
    const char* 	cPtr;
    cPtr = "potato";
    char   buffer[BUFFER_LEN];
    printf("this is the word in cPtr: %s\n",cPtr);

    snprintf(buffer,BUFFER_LEN,"%s","putting some filler in");
    printf("printing the buffer1: %s\n",buffer);
    snprintf(buffer,BUFFER_LEN,"%s","here's some more");
    printf("printing the buffer2: %s\n",buffer);
}
