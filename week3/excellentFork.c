#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define 	MAX_LINE	256

int 	main()
{
	char 		line[MAX_LINE];

	while (1)
	{
		pid_t 	childId;

		printf("Please enter a command: ");
		fgets(line, MAX_LINE, stdin);

		char*	cPtr	= strchr(line, '\n');

		if (cPtr != NULL)
			*cPtr = '\0';
		
		childId = fork();
		
		if (childId == 0)
		{
			execl(line, line, NULL);
			fprintf(stderr, "Could not find %s\n", line);
			exit(EXIT_FAILURE);
		}
	
	}
	
	return(EXIT_FAILURE);
}
