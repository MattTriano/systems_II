#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define 	BUFFER_LEN 	1024

const 	char 	COMMENT_CHAR 	= '#';

int 	main 	(int 	argc,
  		 char* 	argv[]
		)
{
    // Check the argument
    if (argc < 2)
    {
        fprintf(stderr, "Usage:\tlineCounter <string> <filename>\n");
        exit(EXIT_FAILURE);
    }
    // Open the file
    const char* filePath = argv[1];
    FILE* filePtr = fopen(filePath, "r");
    
    if (filePtr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    // Read a lint
    int 	counter = 0;
    int 	lineNum = 0;
    char 	buffer[BUFFER_LEN];

    while (fgets(buffer, BUFFER_LEN, filePtr) != NULL)
    {
        lineNum++;

        char* 	cPtr;

        for (cPtr = buffer;  isspace(*cPtr);  cPtr++);
        if ( (*cPtr == COMMENT_CHAR) || (*cPtr == '\0') )
            continue;

        int i;
        int j;

        if ( sscanf(cPtr, "%d %d", &i, &j) == 2 )
                counter++;
        else
            fprintf(stderr, "Missing integers on line %d\n", lineNum);
    }

    fclose(filePtr);
    printf("%d\n", counter);
    return(EXIT_SUCCESS);

}


    
    

    //  go past the spaces
    //  in  see a COMMENT_CHAR or a blank line: continue
    //  try to read 2 integers
