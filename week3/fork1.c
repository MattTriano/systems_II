#include <stdlib.h>
#include <stdio.h>

int 	main()
{
	int x = 1;
	pid_t pid = fork();

	if (pid == 0)
		printf("Child has x = %d\n", x++);
	else
		printf("Parent has x = %d\n", x--);

	printf("Bye fromm process %d with x = %d\n", getpid(), x);
	
	return(EXIT_SUCCESS);
}
