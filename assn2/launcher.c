#include "assign2Headers.h"

pid_t 	answererPid;
pid_t 	guesserPid;
int 	shouldRun	= 1;

void 	sigAlarmHandler (int sigInt
			)
{
	shouldRun	= 0;
	kill(answererPid, TIME_OVER_SIGNAL);
	kill(guesserPid, TIME_OVER_SIGNAL);
}

void 	sigChldHandler(int sigInt
		       )
{
	pid_t		pid;
	int 		s;
	while((pid = waitpid(-1, &s, WNOHANG)) > 0) {}
	shouldRun 	= 0;
}
	
}

int 	main ()
{
	char			line[MAX_LINE];
	struct 	sigaction	act;
	
	memset(&act, '\0', sizeof(act));
	act.sa_handler = sigChldHandler;
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);
		
}
    
