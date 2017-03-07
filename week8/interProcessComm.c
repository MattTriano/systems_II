#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int  	main	()
{
    int 	parentToChild[2];
    int 	childToParent[2];

    if ((pipe(parentToChild) < 0) || (pipe(childToParent) < 0))
    {
        fprintf(stderr, "Can't make pipes\n");
        return(EXIT_FAILURE);
    }

    int 	pid 	= fork();

    if (pid < 0)
    {
        fprintf(stderr, "Too many processes Ace!\n");
        return(EXIT_FAILURE);
    }
    else
    if (pid == 0)
    {
    
        // Baby's case
        close(0);   // Close "stdin"
        dup(parentToChild[0]);
        close(1);   // Close "stdout"
        dup(childToParent[1]);

        // Baby's case, continued
        while (1)
        {
            char buffer[10];
            int i, numRead;
            numRead = read(0,buffer,10);
  
            for (i=0; i<numRead; i++)
                buffer[i] = toupper(buffer[i]);

            write(1,buffer,numRead);
        }
    }
    else
    {
        // Mama's case
        while (1)
        {
            char buffer[10];
            fgets(buffer,10,stdin);
            write(parentToChild[1], buffer, 10);
            read (childToParent[0], buffer, 10);
            printf(buffer);
        }
    }
    return(EXIT_SUCCESS);
}


