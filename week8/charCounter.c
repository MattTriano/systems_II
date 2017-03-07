#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define       BUFFER_SIZE     256

/* Write a program that counts the number of occurrences
 of a character given on the command line. */

int 	main (	int 		argc, 
		const char* 	argv[]
	     )
{
    if  (argc < 3)
    {
        fprintf(stderr,"Usage: charCount <char> <file>\n");
        return(EXIT_FAILURE);
    }
    const char 		charToCount = *argv[1];
    const char* 	fileCPtr    = argv[2];

    /* YOUR CODE HERE */
    int fd 	= open(fileCPtr, O_RDONLY, 0);

    if (fd < 0)
    {
        fprintf(stderr, "Could not open %s\n", fileCPtr);
        exit(EXIT_FAILURE);
    }

    char 	buffer[BUFFER_SIZE];
    int 	numBytes;
    int 	counter = 0;

    while 	( (numBytes = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        const char* run;
        const char* stop = buffer + numBytes;

        for (run = buffer; run < stop; run++)
            if (*run == charToCount)
                counter++;
    }

    close(fd);
    printf("%d\n", counter);
    return(EXIT_SUCCESS);
}
