#include  <stdlib.h>
#include <stdio.h>

char begin;
char end;

extern void enterBeginEnd ();

extern void printFromBeginToEnd ();

int main ()
{
  enterBeginEnd();
  printFromBeginToEnd();

  return(EXIT_SUCCESS);
}
