#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME 		"bubu.txt"

int 	main ()
{
    int fd = open(FILENAME, )_WRONLY|O_TRUNC|O_CREAT, 0660);

    close(1);
    dup(fd);
    printf("I wonder where this will show up?");
    close(FD);
    return(EXIT_SUCCESS);
}
