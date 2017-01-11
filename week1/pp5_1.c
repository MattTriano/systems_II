#include <stdlib.h>
#include <stdio.h>

void swap(long *xp, long *yp)
{
  *xp = *xp + *yp;
  *yp = *xp - *yp;
  *xp = *xp - *yp;
}


