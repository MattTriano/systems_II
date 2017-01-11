#include "header.h"

#define ARRAY_LEN	16

void enterBeginEnd()
{
  char array[ARRAY_LEN];
  printf("Enter the beginning character: ");
  fgets(array, ARRAY_LEN, stdin);
  begin = array[0];
  do
  {
    printf("Enter the end character: ");
    fgets(array, ARRAY_LEN, stdin);
    end = array[0];
  }
  while (end < begin);
}
