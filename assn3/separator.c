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

struct  Word*  		obtainCommaSeparatedList( const char* string) {
    const char 		comma 	 	= ',';
    char*  		charRun  	= strchr(string, comma); // pointer to next comma
    int 		length 	 	= strlen(string);
    struct  Word*	toReturn 	= (struct Word*)malloc(sizeof(struct Word));
    size_t  		wordLen		= (charRun - string + 1);
    char* 		wordText 	= (char*)malloc(wordLen);
    
    strncpy(wordText, string, wordLen);
        
    toReturn->textPtr_ = wordText;
    toReturn->nextPtr_ = obtainCommaSeparatedList( // the remainder of the string
    // want to allocate space from wordBeginning to charRun
    // want to use strncpy to get text from that length
    // make a Word object with (copiedText, charRun) as values
    // free things

    return(toReturn);
            
}

int main () {
    char 	  	line[MAX_LINE];
    char*  	  	cPtr;
    char* 	 	charRun;
    struct  Word*  	splitList;
    char* 		initChar;
    char* 		commaChar;

    printf("Enter the comma-separated words to be delimited: ");
    fgets(line, MAX_LINE, stdin);

    cPtr  	= strchr(line,'\n');
    initChar  	= &line;
    commaChar 	= strchr(line, ',');
    printf("this is initChar: %s \n", initChar);
    printf("this is the length between initChar and commaChar: %d \n", (commaChar - initChar));


//    if (cPtr != NULL) {
//         *cPtr = '\0';
//         splitList 	= obtainCommaSeparatedList(line);
//    } else {
//         printf("Invalid string entered; program terminating. \n");
//         printf("Enter something longer next time \n");

//    printf("the entered sentence is %s \n", line);
//    printf("the value in cPtr is %s \n", strchr(line, '\n'));

    return(EXIT_SUCCESS);
}
