#include <stdlib.h> 
#include <stdio.h> 
#include <ctype.h> // for isupper(), tolower(), toupper() 
#include <sys/types.h> // for open() 
#include <sys/stat.h> // for open() 
#include <fcntl.h> // for open()

#define BUFFER_LEN 256

int main (int argc, 
          char* argv[] ) 
{  
    int inFd = open(argv[1],O_RDONLY,0);  
    int outFd = open(argv[2],O_WRONLY,0640);  
    char buffer[BUFFER_LEN];  
    int numChars;

    if (inFd > 0 || outFd > 0) {
        fprintf(stderr,"couldn't open these files\n");
        return(EXIT_FAILURE);
    }
    
    while  ( (numChars = read(inFd,buffer,BUFFER_LEN)) > 0 )  
    {    
        int i;
        for  (i = 0;  i < numChars;  i++)      
            if  ( isupper(buffer[i]) ) 
                buffer[i] = tolower(buffer[i]);      
                strn
            else 
                buffer[i] = toupper(buffer[i]);
    
        write(outFd,buffer,numChars);  
    }
    printf("All done!  Please press enter.");  
    gets(buffer);
    return(EXIT_SUCCESS); 
}
