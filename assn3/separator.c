#include        <stdlib.h>
#include        <stdio.h>
#include        <unistd.h>
#include        <pthread.h>
#include 	<string.h>

//  PURPOSE:  To tell the length of char arrays.
const  int  		MAX_LINE = 256;

struct  		Word
{
    char* 		textPtr_;
    struct  Word* 	nextPtr_;
};

//struct  Word*  		obtainCommaSeparatedList( const char* string) {
        
//}

int main () {
    char 	  	line[MAX_LINE];
    char*  	  	cPtr;
    struct  Word*  	commaSepList = (struct Word*)malloc(sizeof(struct Word));

    printf("Enter the comma-separated words to be delimited: ");
    fgets(line, MAX_LINE, stdin);
    int 		initLen = strlen(line);
    printf("strlen of this line is: %i \n", initLen);    
    char*               noNewLine[initLen-1];
    strncpy(noNewLine, line, initLen);
    printf("strncpy of this line is: %s", noNewLine);
    printf("|| no gap shows it worked");

    if (strlen(line) > 0) {
        cPtr = strchr(line,'\n');
        if (cPtr != NULL) 
            *cPtr = '\0';
    }

    printf("the entered sentence is %s \n", line);
    printf("the value in cPtr is %s \n", strchr(line, '\n'));

    return(EXIT_SUCCESS);
}
