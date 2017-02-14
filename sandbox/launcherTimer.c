/*-------------------------------------------------------------------------*
 *------*
 *---launcherTimer.c---*
 *------*
 *---    This files defines a silly program that launches another---*
 *---program, and gives it 'TIME_LIMIT_NUM_SECONDS' seconds to---*
 *---finish.  If it finishes in time it prints "Congratulations!".---*
 *---If not, it forces it to finish by sending it SIGINT.---*
 *------*
 *--------------------------------------*
 *------*
 *---Version 1.02016 July 26Joseph Phillips---*
 *------*
 *-------------------------------------------------------------------------*/
#include	"headers.h"
#include <sys/types.h>// pid_t
#include <sys/wait.h>//  wait
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>


/*
-> sigChildHandler() is mostly written, but it should wait for the child so it does not stay a zombie process.
-> main() is mostly written, but it should install sigChildHandler() as the handler for SIGCHLD.
It should also make a new process, put the id in childId, and have the child process run ANSWERER_PROG.
-> Lastly, it should stop the its child process after the for-loop by sending it SIGINT if it has not already stopped.*/




//Global variable definition:
int	isTimeUp 	= 0;//  PURPOSE:  To hold '1' when the time is up, or '0' before then.
int	didChildStop 	= 0;//  PURPOSE:  To hold '1' after the child has stopped, or '0' before then.



//
//Global function definition:
//
//  PURPOSE:  To handle when the child process has stopped by unzombie-ing it.
//    Ignores 'sig'.  No return value.
void	sigChildHandler(int sig){
    //the wait should be here
    wait(NULL);


   if  (isTimeUp)
    printf("Timer: \"Sorry, time is up!\"\n");
  else
    printf("Timer: \"Congratulations!\"\n");

  didChildStop   = 1;

}

//  PURPOSE:  To run the program.  Ignores parameters.  Sends 'EXIT_SUCCESS'
//to OS.


int	main(){
  //  I.  Application validity check:
  //  II.  Do program:
  pid_t		childId;

  //Do something here

   //sigChildHandler
    struct sigaction act;
    memset(&act,'\0',sizeof(struct sigaction));
    act.sa_handler = sigChildHandler;
    sigaction(SIGINT  , &act, NULL);

  //Launch answerer
   childId=fork();
   if(childId ==0){
    execl(ANSWERER_PROG,ANSWERER_PROG,NULL);
   }



  int secs;

  for  (secs = TIME_LIMIT_NUM_SECONDS;  (secs > 0) && !didChildStop;  secs--)
  {
    printf("Timer: \"%d seconds\"\n",secs);
    sleep(1);
  }

  isTimeUp= 1;

  if  (!didChildStop)
  {
    printf("Timer: \"%d seconds\"\n",secs);
    //  Stop the child process by sending it SIGINT
    kill(childId,SIGINT);
  }

  /*while  (!didChildStop ){//this was causing a bug in my code, not sure that this should be added in the code!
   sleep(1);
 }*/

   return(EXIT_SUCCESS);
}
