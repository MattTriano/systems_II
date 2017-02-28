#include 	<stdlib.h>
#include 	<stdio.h>
#include 	<string.h>

#define 	BUFFER_LEN 	1024

int 	main (int 	argc,
	      char* 	argv[]
 	     )
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage:\tlineCounter <string> <filename>\n");
        exit(EXIT_FAILURE);
    }

    const char* 	lookFor 	= argv[1];
    const char* 	filePath 	= argv[2];
    FILE* 		filePtr 	= fopen(filePath, "r");

    if (filePtr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    int 	counter 	= 0;
    int 	lookForLen 	= strlen(lookFor);
    char 	buffer[BUFFER_LEN];

    while (fgets(buffer, BUFFER_LEN, filePtr) != NULL)
    {
        if (strncmp(buffer, lookFor, lookForLen) == 0)
            counter++;
    }

    fclose(filePtr);
    printf("%d\n", counter);
    return(EXIT_SUCCESS);
}
