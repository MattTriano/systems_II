#include <stdlib.h>
#include <stdio.h>

int 	main()
{
	puts("L0");
	fork();
	puts("L1");
	fork();
	
	printf("Bye from process %d\n", getpid());
	
	
	return(EXIT_SUCCESS);
}
