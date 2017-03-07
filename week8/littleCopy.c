#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 256

int 	main(	int		argc,
 	 	const char*	argv[]
	    )
{
  const char* fromFileCPtr;
  const char* toFileCPtr;

  if (argc < 3)
  {
    fprintf(stderr,"Usage: littleCopy <fromFile> <toFile>\n");
    return(EXIT_FAILURE);
  }

  fromFileCPtr = argv[1];
  toFileCPtr = argv[2];

  /* YOUR CODE HERE */
  intfromFd= open(fromFileCPtr,O_RDONLY,0);

  if  (fromFd < 0)
  {
    fprintf(stderr,"Could not open %s\n",fromFileCPtr);
    exit(EXIT_FAILURE);
  }

  inttoFd= open(toFileCPtr,O_WRONLY|O_CREAT|O_TRUNC,0660);

  if  (toFd < 0)
  {
    fprintf(stderr,"Could not open %s\n",toFileCPtr);
    exit(EXIT_FAILURE);
  }

  char 		buffer[BUFFER_SIZE];
  int	 	numBytes;

  while  ( (numBytes = read(fromFd,buffer,BUFFER_SIZE)) > 0)
    write(toFd,buffer,numBytes);

  close(toFd);
  close(fromFd);


  return(EXIT_SUCCESS);
}

