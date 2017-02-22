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
    printf("just entered a new iteration, string = %s \n", string);
    printf("string length = %d \n", strlen(string));
    char*  		charRun  	= strchr(string, ','); // pointer to next comma
    size_t 		wordLen;
    size_t              length          = strlen(string);
    struct  Word*       toReturn        = (struct Word*)malloc(sizeof(struct Word));
    char* 		stringRemnant;

    if (charRun != NULL) {
        charRun  	+= 1;
        printf("charRun is not NULL \n");
        wordLen 	= (charRun - string - 1);
        stringRemnant   = (char*)malloc(length - wordLen);
        strncpy(stringRemnant, charRun, (length - wordLen + 1));
    } else {
        printf("charRun is NULL \n");
        wordLen  	= length;
        stringRemnant  	= string;
    }
//    int 		length 	 	= strlen(string);
    printf("right after setting length, length = %d \n", length);
//    printf("right before setting wordLen: charRun = %s \n", charRun);
    printf("banal stuff \n");
//    size_t  		wordLen		= (charRun - string - 1);
    char* 		wordText 	= (char*)malloc(wordLen+1);
//    char* 		stringRemnant 	= (char*)malloc(length - wordLen);
        
    printf("debug: wordLen 		= %d \n", wordLen);
    printf("debug: stringLength 	= %d \n", length); 
    strncpy(wordText, string, wordLen);
    printf("problem not in the wordText assignment \n");
    printf("charRun = %s \n", charRun);
//    strncpy(stringRemnant, charRun, (length - wordLen + 1));    
    printf("Pre recn: length 	    = %d \n", length);
    printf("Pre recn: wordLen       = %d \n", wordLen);    
    printf("Pre recn: wordText      = %s \n", wordText);
    printf("Pre recn: charRun       = %s \n", charRun);
    printf("Pre recn: stringRemnant = %s \n", stringRemnant);  
    toReturn->textPtr_ = wordText;


    if (charRun == NULL) {
//    if (endCond != NULL && charRun == NULL) {    
//        toReturn->textPtr_ = wordText;
        printf("entering the recursion termination section");
        toReturn->nextPtr_ = NULL ;
        free(stringRemnant);
        free(wordText);
        free(toReturn);
        return(toReturn);
    } else {
        printf("in rec loop: stringRemnant = %s \n", stringRemnant);
        printf("in rec loop: remnantLength = %d \n", strlen(stringRemnant));
        toReturn->nextPtr_ = obtainCommaSeparatedList(stringRemnant); // the remainder of the string
        
    }
        // want to allocate space from wordBeginning to charRun
        // want to use strncpy to get text from that length
        // make a Word object with (copiedText, charRun) as values
        // free things
        printf("Post recursion: wordText = %s \n", wordText);
        free(stringRemnant);
        free(wordText);
        free(toReturn);

    return(EXIT_FAILURE);
            
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

    printf("this is the remainder: %s \n", commaChar);

    if (cPtr != NULL) {
         *cPtr = '\0';
         splitList 	= obtainCommaSeparatedList(line);
    } else {
         printf("Invalid string entered; program terminating. \n");
         printf("Enter something longer next time \n");
    }
//    printf("the entered sentence is %s \n", line);
//    printf("the value in cPtr is %s \n", strchr(line, '\n'));

    return(EXIT_SUCCESS);
}
