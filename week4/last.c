#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define 	LINE_LEN	256

int 		shouldContinue = 1;

void 	sigAlarmHandler (int sigInt
			)
{
	shouldContinue = 0;
}


void	sigIntHandler   (int	sigInt
			)
{
	char	line[LINE_LEN];
	int 	remainingSecs	=	alarm(0);

	printf("%d seconds remain, press enter to continue: ", remainingSecs);
	fgets(line, LINE_LEN, stdin);
	alarm(remainingSecs);
}

int 	main 	()
{

	char			line[LINE_LEN];
	int			numSecs;
	struct	sigaction	act;
	
	memset(&act, '\0', sizeof(act));
	act.sa_handler = sigAlarmHandler;
	sigaction(SIGALRM, &act, NULL);

	printf("Please enter the number of seconds before the alarm goes off: ");
	fgets(line, LINE_LEN, stdin);
	numSecs = strtol(line, NULL, 10);
	
	alarm(numSecs);

	while (shouldContinue)
		printf("Tick Tock\n");
	
	printf("Ding! Ding! Ding! \n");
	return(EXIT_SUCCESS);	

}
