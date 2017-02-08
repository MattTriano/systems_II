#include "assign2Headers.h"

pid_t 		answererPid;
pid_t 		guesserPid;
int 		shouldRun = 1;

void sigAlrmHandler (int sigInt) {
	kill(answererPid, TIME_OVER_SIGNAL);
	kill(guesserPid, TIME_OVER_SIGNAL);
	shouldRun = 0;
}

void sigChldHandler(int sigInt) {
	pid_t	pid;
	int 	s;
	while((pid = waitpid(-1, &s, WNOHANG)) > 0) {
		if (WIFEXITED(s) != 0)
			printf("%d returned %d\n", pid, WEXITSTATUS(s));
		else
			printf("%d crashed!\n", pid);
		}
	shouldRun = 0;
}



int main ()
{
	char			line[LINE_LEN];
	struct 	sigaction	actC;
	struct  sigaction       actA;
	int 			status = 1;

	memset(&actC, '\0', sizeof(actC));
	actC.sa_handler = sigChldHandler;
	actC.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	sigaction(SIGCHLD, &actC, NULL);

	memset(&actA, '\0', sizeof(actA));
        actA.sa_handler = sigAlrmHandler;
//        actA.sa_flags = SA_NOCLDSTOP | SA_RESTART;
        sigaction(SIGALRM, &actA, NULL);

	pid_t childPid1 = fork();
	printf("childPid1 = %d (l47, lau) \n", childPid1);
	if (childPid1 == 0) {
		status = 0;
		answererPid = getpid();
		printf("the pid for the answerer process is %d (line49, launcher)\n", answererPid);
		execl(ANSWERER_PROGNAME,ANSWERER_PROGNAME, NULL);
		fprintf(stderr, "Could not find %s\n", ANSWERER_PROGNAME);
		exit(EXIT_FAILURE);
	}

	alarm(NUM_SECONDS);
//	waitpid(answererPid, &status, 0);
	pid_t childPid2 = fork();

	if (childPid2 == 0) {
		guesserPid = getpid();
		printf("the pid for the answer process is %d (line61, launcher)\n", answererPid);
		printf("the pid for the guesser process is %d (line62, lanucher)\n", guesserPid);
		snprintf(line, LINE_LEN, "%d", answererPid);
		execl(GUESSER_PROGNAME, GUESSER_PROGNAME, line, NULL);
		fprintf(stderr, "Could not find %s\n", GUESSER_PROGNAME);
		exit(EXIT_FAILURE);
	}

//	if (WIFEXITED(status)) {
//		guesserPid = getpid();
//		printf("the pid for the process when childPid != 0 is %d\n", guesserPid);
//		snprintf(line, LINE_LEN, "%d", answererPid);
//		execl(GUESSER_PROGNAME, GUESSER_PROGNAME, line, NULL);
//		fprintf(stderr, "Could not find %s\n", GUESSER_PROGNAME);
//		exit(EXIT_FAILURE);
//}

	while (shouldRun)
		sleep(1);

	sleep(1);
	sleep(1);

	printf("launcher finished\n");
	return(EXIT_SUCCESS);
}
