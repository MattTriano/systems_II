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
    char*  		charRun  	= strchr(string, ','); // pointer to next comma
    size_t 		wordLen;
    size_t              length          = strlen(string);
    struct  Word*       toReturn        = (struct Word*)malloc(sizeof(struct Word));
    char* 		stringRemnant;

    if (charRun != NULL) {
        charRun  	+= 1;
        wordLen 	= (charRun - string - 1);
        stringRemnant   = (char*)malloc(length - wordLen);
        strncpy(stringRemnant, charRun, (length - wordLen + 1));
    } else {
        wordLen  	= length;
        stringRemnant  	= string;
    }

    char* 		wordText 	= (char*)malloc(wordLen+1);       
    strncpy(wordText, string, wordLen);
    toReturn->textPtr_ = wordText;

    if (charRun == NULL) {
        toReturn->nextPtr_ = NULL ;
        free(wordText);
        free(stringRemnant);
        return(toReturn);
    } else {
        toReturn->nextPtr_ = obtainCommaSeparatedList(stringRemnant); // the remainder of the string       
    }
    return(toReturn);           
}

void 		printCommaSeparatedList(const struct Word* list) {
    printf("Word text = \"%s\" \n", list->textPtr_);
    if (list->nextPtr_ == NULL)
        return;
    printCommaSeparatedList(list->nextPtr_);
}

void 		freeCommaSeparatedList(struct Word* list) {
    if (list->nextPtr_ == NULL) {
        free(list->textPtr_);
        return;
    }
    free(list->textPtr_);
    freeCommaSeparatedList(list->nextPtr_);
    printf("freed the node!\n");
    free(list->nextPtr_);    
}

int main () {
    char 	  	line[MAX_LINE];
    char*  	  	cPtr;
    char* 	 	charRun;
    struct  Word*  	splitList;
    char* 		initChar;
    char* 		commaChar;

    printf("Please enter a line of text (with commas): ");
    fgets(line, MAX_LINE, stdin);

    cPtr  	= strchr(line,'\n');

    if (cPtr != NULL) {
        *cPtr = '\0';
        splitList 	= obtainCommaSeparatedList(line);
        printCommaSeparatedList(splitList);
        freeCommaSeparatedList(splitList);
    } else {
        printf("Invalid string entered; program terminating. \n");
        printf("Enter something longer next time \n");
    }

    return(EXIT_SUCCESS);
}
