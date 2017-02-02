/* 	Setup	*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const int N = 16;

int main ()
{
	pid_t 	pid[N];
	int 	i;
	int 	status;
	
	/* Making babies
	   How many second does the FIRST baby wait?
 	   How many second does the LAST baby wait?
	*/
	for (i = 0; i < N; i++)
		if ((pid[i] = fork()) == 0)
		{
			/* Child case */
			sleep(N-i);
			return(100+i);
		}

	/* waiting for babies (babysitting?) */
	for (i=0; i < N; i++)
	{
		pid_t childPid = waitpid(pid[i], &status, 0);

		if (WIFEXITED(status))
			printf("Child $%d ended with status %d\n", 
			  childPid, WEXITSTATUS(status));
		else 
			printf("Child %d ended abnormally\n", childPid);
	}
}
