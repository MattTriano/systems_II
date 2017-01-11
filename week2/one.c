#include <stdlib.h>
#include <stdio.h>

int start = 0;
int stop  = 100;

extern int sum();

int main ()
{
  printf("Sum from %d to %d is %d\n", start, stop, sum() );
  return(EXIT_SUCCESS);
}
