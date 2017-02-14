/*nswerer.c---*
 *------*
 *---    This files defines a program that chooses a random integer,---*
 *---launches another program, and lets that program guess the---*
 *---integer.
 *------*
 *--------------------------------------*
 *------*
 *---Version 1.02016 July 26Joseph Phillips---*
 *------*
 *-------------------------------------------------------------------------*/

//
//Header inclusion:
//

#include"headers.h"
#include <sys/types.h>// pid_t
#include <sys/wait.h>//  wait
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>


//
//Global variable definition:
//

//  PURPOSE:  To hold the process id of the process that guesses the number
//held by this ansewering process.
pid_t	guesserId;


//  PURPOSE:  To hold the answer to be guessed.
int	answer;


//  PURPOSE:  To hold the binary place currently being guessed.
int	binaryPlace;


//  PURPOSE:  To hold '1' while this program should continue to run, or '0'
//otherwise.
int	shouldContinue= 1;


//
//Global function definition:
//



//  PURPOSE:  To handle when the guesser correctly guess that digit 'digit' is
//at binary position 'binaryPlace'.  No return value.
void	correctGuess(int	digit)
{
  if  (digit)
    printf("Answerer: \"Yes, there is a %d.\"\n",binaryPlace);
  else
    printf("Answerer: \"Yes, there is no %d.\"\n",binaryPlace);

  binaryPlace = binaryPlace >> 1;
  //  Tell the guessing process that it guessed correctly
    kill(guesserId,CORRECT_SIG );
}


//  PURPOSE:  To handle when the guesser incorrectly guess that digit 'digit' is
//at binary position 'binaryPlace'.  No return value.
void	incorrectGuess(intdigit)
{
  printf("Answerer: \"Sorry, guess again.\"\n");
  //  Tell the guessing process that it guessed incorrectly
  kill(guesserId,INCORRECT_SIG );

}


//  PURPOSE:  To handle when the guesser guesses that a '0' is at binary
//position 'binaryPlace'.  Ignores 'sig'.  No return value.
void	zeroSigHandler(intsig)
{
  if  ( (answer & binaryPlace) == 0 )
    correctGuess(0);
  else
    incorrectGuess(0);
}


//  PURPOSE:  To handle when the guesser guesses that a '1' is at binary
//position 'binaryPlace'.  Ignores 'sig'.  No return value.
void	oneSigHandler(intsig)
{
  if  ( (answer & binaryPlace) == binaryPlace )
    correctGuess(1);
  else
    incorrectGuess(1);
}


//  PURPOSE:  To handle when the timing process tells this process that the
//time is up.  Ignores 'sig'.  No return value.
void	sigIntHandler(intsig)
{
  printf("Answerer: \"Whoops, time is up!\"\n");
  shouldContinue= 0;
  //  Tell the guessing process that the time is up by sending it SIGINT
  kill(guesserId,SIGINT);
}


//  PURPOSE:  To run answering program.  Ignore command line arguments.
//Returns 'EXIT_SUCCESS' to OS.
int	main()
{



  srand(getpid());
  rand();
  answer= rand() % 128;
  binaryPlace= 1 << 7;

  printf("Answerer: \"(Don't tell, but the answer is %d)\"\n",answer);

  //  Install signal handlers


    //zeroSigHandler
    struct sigaction act3;
    memset(&act3,'\0',sizeof(struct sigaction));
    act3.sa_handler = zeroSigHandler;
    sigaction(ZERO_SIG, &act3, NULL);

    //oneSigHandler
    struct sigaction act4;
    memset(&act4,'\0',sizeof(struct sigaction));
    act4.sa_handler = oneSigHandler;
    sigaction(ONE_SIG, &act4, NULL);

    //sigIntHandler
    struct sigaction act5;
    memset(&act5,'\0',sizeof(struct sigaction));
    act5.sa_handler = sigIntHandler;
    sigaction(SIGINT, &act5, NULL);


  //  Start guessing process, put process id in 'guesserId'
    guesserId=fork();
    if (guesserId==0) { // child process
        execl(GUESSER_PROG,GUESSER_PROG,NULL);
    }




  while  (shouldContinue && (binaryPlace > 0))
    sleep(1);


  // Wait for guessing process here
  wait(NULL);


  return(EXIT_SUCCESS);
}
