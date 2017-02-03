#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define	LINE_LEN	16

void 	sigIntHandler 	(int 		sigInt, 
			 siginfo_t*	infoPtr,
			 void*		dataPtr
			)

{	
	if (infoPtr -> si_pid == getppid())
		printf("Hee-Hee! that tickles!\n");
	else
		printf("NO TOUCHING!\n");
}

int main ()
{
	pid_t 	childId = fork();

	if (childId == 0)
	{
		struct	sigaction 	act;

		memset(&act,'\0', sizeof(act));
		act.sa_flags 	 = SA_SIGINFO;
		act.sa_sigaction = sigIntHandler;
		sigaction(SIGINT, &act, NULL);

		while (1)
			sleep(1);
		
		exit(EXIT_SUCCESS); 
	}
	
	int 	i;
	char 	line[LINE_LEN];

	for(i = 0; i < 4; i++)
	{
		printf("Please enter to tickle the Elmo: ");
		fgets(line, LINE_LEN, stdin);
		kill(childId, SIGINT);
	}
	return(EXIT_SUCCESS);
}
