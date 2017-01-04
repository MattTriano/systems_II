#include <stdlib.h>
#include <stdio.h>
#define TEXT_LEN 64
int main() {
  char   text[TEXT_LEN];
  char* cPtr;
  while (1)
  {
    printf("Please enter a number: ");
    fgets(text, TEXT_LEN, stdin);
    int i = strtol(text, &cPtr, 0);
    if (cPtr == text)
      printf("Phooey!\n");
    else
      printf("dex:\t%d\n"
             "hex:\t%X\n",i,i);
  }
  return(EXIT_SUCCESS);
}









 
