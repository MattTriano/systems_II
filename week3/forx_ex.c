#include <stdlib.h>
#include <stdio.h>

int 	bss 	= 0;
int 	data 	= 1;

int main ()
{
  int 	stack 		= 0;
  int* 	heapPtr		= (int*)malloc(sizeof(int));

  *heapPtr 		= 4;

  pid_t pid 		= fork();
  
  if (pid == 0)
  {
    bss 	+= 2;
    data 	+= 2;
    stack 	+= 2;
    (*heapPtr)	+= 2;
  }
  else
  {
    bss 	+= 1;
    data 	+= 1;
    stack 	+= 1;
    (*heapPtr)	+= 1;
  } 
  printf("Process %d: bss = %d, data = %d, stack = %d, heap = %d\n", 
         getpid(), bss, data, stack, *heapPtr);

  return(EXIT_SUCCESS);
}
