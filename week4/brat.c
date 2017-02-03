#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

int main ()
{
	struct 	sigaction	act;
	memset(&act, '\0', sizeof(struct sigaction));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &cow, NULL);

	while (1)
	{
		printf("Ngyeah-ngyeah, you can't stop me!\n");
		speel(2);
	}
	return(EXIT_SUCCESS);
}
