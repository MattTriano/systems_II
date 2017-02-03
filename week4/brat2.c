#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

void 	simpleHandler (int	sigInt)
{
	switch (rand() % 4)
	{
	case 0:
		printf("ooch\n");
		break;
	case 1:
		printf("Stop it!\n");
		break;
	case 2:
		printf("case 2!\n");
		break;
	case 3:
		printf("case D!\n");
		break;
	}
}


int main ()
{
	struct 	sigaction	act;
	memset(&act, '\0', sizeof(struct sigaction));
	act.sa_handler = simpleHandler;
	sigaction(SIGINT, &act, NULL);

	while (1)
	{
		printf("Ngyeah-ngyeah, you can't stop me!\n");
		speel(2);
	}
	return(EXIT_SUCCESS);
}
