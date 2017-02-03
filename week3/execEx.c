#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main ()
{
	char line[100];
	printf("What program do you want to run? ");
	fgets(line, 100, stdin);

	char* cPtr = strchr(line, '\n');
	if (cPtr != NULL)
		*cPtr = '\0';

	execl(line, line, NULL);
	printf("Will this line be printed?\n");
	return(EXIT_SUCCESS);
}
