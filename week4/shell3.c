#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define MAX_LINE 256

void sigChldHander (int sig)
{
  pid_t pid;
  int s;

  while( (pid=waitpid(-1,&s,WNOHANG)) > 0)
  {
    if (WIFEXITED(s) != 0)
      printf("%d returned %d\n",pid,WEXITSTATUS(s));
    else
      printf("%d crashed!\n",pid);
  }
}

int main()
{
  char   line[MAX_LINE];
  struct sigaction action;

  memset(&action,'\0',sizeof(action));
  action.sa_handler= sigChldHander;
  action.sa_flags = SA_NOCLDSTOP |SA_RESTART;
  sigaction(SIGCHLD,&action,NULL);

  while  (1)
  {
    pid_t childId;

    printf("Please enter a command: ");
    fgets(line,MAX_LINE,stdin);

    char* cPtr= strchr(line,'\n');

    if  (cPtr != NULL)
      *cPtr = '\0';

    childId = fork();

    if  (childId == 0)
    {
      execl(line,line,NULL);
      fprintf(stderr,"Could not find %s\n",line);
      exit(EXIT_FAILURE);
    }

  }

  return(EXIT_SUCCESS);
}
