#include "assign2Headers.h"

pid_t 	answererPid;
pid_t 	guesserPid;
int 	shouldRun	= 1;

void 	sigAlrmHandler (int sigInt)
{
	kill(answererPid, TIME_OVER_SIGNAL);
	kill(guesserPid, TIME_OVER_SIGNAL);
	shouldRun 	= 0;
}

void 	sigChldHandler(int sigInt)
{
	pid_t		pid;
	int 		s;
	while((pid = waitpid(-1, &s, WNOHANG)) > 0) {}
	shouldRun 	= 0;
}
	


int 	main ()
{
	char			line[LINE_LEN];
	struct 	sigaction	actC;
	struct  sigaction       actA;	

	memset(&actC, '\0', sizeof(actC));
	actC.sa_handler = sigChldHandler;
	actC.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	sigaction(SIGCHLD, &actC, NULL);

	memset(&actA, '\0', sizeof(actA));
        actA.sa_handler = sigAlrmHandler;
        actA.sa_flags = SA_NOCLDSTOP | SA_RESTART;
        sigaction(SIGCHLD, &actA, NULL);
	
	answererPid = fork();	
			
}
    
