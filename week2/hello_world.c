#include <stdlib.h>
#include <stdio.h>

int OS_EVERYTHING_OKAY     = 0;
int OS_NOT_EVERYTHING_OKAY = 1;

#define MSG  "Hello world!\n"

void hello_world()
{
  printf(MSG);
}

int main()
{
  hello_world();
  return(OS_EVERYTHING_OKAY);
}
