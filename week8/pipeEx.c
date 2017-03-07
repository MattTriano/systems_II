#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int PIPE_READ 	= 0;
const int PIPE_WRITE 	= 1;

int myPipe[2];

int main()
{
    if (pipe(myPipe) == 0)
    {
        char myArray[8];

        write(myPipe[PIPE_WRITE], "hello!\n", 8);
        read (myPipe[PIPE_READ], myArray, 8);
        printf(myArray);
    }
    return(EXIT_SUCCESS);
}
