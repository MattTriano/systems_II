#include <stdlib.h>
#include <stdio.h>

extern char begin;
extern char end;

void printFromBeginToEnd ()
{
  char i;

  for (i = begin; i <= end; i++)
    printf("%d %c\n", i, i);
}
