#include 	<stdlib.h>
#include	<stdio.h>
#include 	<unistd.h>
#include 	<wait.h>

void 	runChild (const char* progName);

int 	main ()
{
	runChild("./iSucceed");
	runChild("./iFail");
	runChild("./iCrash");
	return(EXIT_SUCCESS);
}

void 	runChild(const char* progName)
{
	int 	status;
	pid_t	childId;
	
	printf("Running %s:\n", progName);

	if (fork() == 0)
	{
		// The child case:
		execl(progName, progName, NULL);
		fprintf(stderr, "Could not find %s\n", progName);
		exit(EXIT_FAILURE);
	}

	// The parent case:
	childId = wait(&status);

	if (WIFEXITED(status) )
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			printf("%d succeeded. \n\n", childId);
		else
			printf("%d failed but didn't crash. \n\n", childId);
	}
	else
		printf("%d crashed. \n\n", childId);
}
