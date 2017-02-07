#include "assign2Headers.h"

int	shouldRun 	= 1;

void	sigTimeHandler(int sigInt) {
	printf("Too slow man, were you even paying attention?\n");
	shouldRun = 0;
}

void 	sigWinHandler(int sigInt) {
	printf("You won, you guessed it, you're the greatest!\n");
	shouldRun = 0;
}

void 	sigGuessHandler(int success) {
	if (success)
		printf("Your last guess was correct!\n");
	else
		printf("Your last guess was incorrect.  Let's try again from the beginning. \n");
}

int main (int argc, char* argv[]) 
{	int 			guess;
	
	char 			line[LINE_LEN];
	struct 	sigaction	actTime;
	struct 	sigaction	actWin;
	struct	sigaction	actCor;
	struct 	sigaction	actIncor;
	int 			guess;

	if (argc < 2)
		printf("You only passed %d arguments.  You gotta give me more!\n", argc);
		return(EXIT_FAILURE);
	
	pid_t answererPid = strtol(argv[1], NULL, 10);

	memset(&actTime, '\0', sizeof(actTime));
	actTime.sa_handler = sigTimeHandler;
	actTime.sa_flags   = SA_NOCLDSTOP | SA_RESTART;
	sigaction(TIME_OVER_SIGNAL, &actTime, NULL);

	memset(&actWin, '\0', sizeof(actWin));
        actWin.sa_handler = sigWinHandler;
        actWin.sa_flags   = SA_NOCLDSTOP | SA_RESTART;
        sigaction(WIN_SIGNAL, &actWin, NULL);

	memset(&actCor, '\0', sizeof(actCor));
        actCor.sa_handler = sigGuessHandler;
        actCor.sa_flags   = SA_NOCLDSTOP | SA_RESTART;
        sigaction(CORRECT_SIGNAL, &actCor, NULL);

	memset(&actIncor, '\0', sizeof(actIncor));
        actIncor.sa_handler = sigGuessHandler;
		guess = 
        actIncor.sa_flags   = SA_NOCLDSTOP | SA_RESTART;
        sigaction(INCORRECT_SIGNAL, &actIncor, NULL);

	while(shouldRun) {
		printf("What would you like your next guess to be: 0 or 1? \n");
		fgets(line, LINE_LEN, stdin);
		guess = (int) strtol(line, NULL, 10);
		if (guess == 1)
			kill(answererPid, ONE_SIGNAL);
		else if (guess == 0)
			kill(answererPid, ZERO_SIGNAL);
		else
			kill(answererPid, INCORRECT_SIGNAL);
		sleep(1);
		
	printf("guesser finished\n");
	return(EXIT_SUCCESS);
}

