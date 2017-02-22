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
        printf("charRun = %s \n", charRun);
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
        printf("entering the recursion termination section");
        toReturn->nextPtr_ = NULL ;
        free(wordText);
        free(stringRemnant);
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

    printf("Enter the comma-separated words to be delimited: ");
    fgets(line, MAX_LINE, stdin);

    cPtr  	= strchr(line,'\n');
    initChar  	= &line;
    commaChar 	= strchr(line, ',');
    printf("this is initChar: %s \n", initChar);
    printf("this is the length between initChar and commaChar: %d \n",(int)(commaChar - initChar));

    printf("this is the remainder: %s \n", commaChar);

    if (cPtr != NULL) {
        *cPtr = '\0';
        splitList 	= obtainCommaSeparatedList(line);
        printCommaSeparatedList(splitList);
        freeCommaSeparatedList(splitList);
    } else {
        printf("Invalid string entered; program terminating. \n");
        printf("Enter something longer next time \n");
    }
    printf("the entered sentence is %s \n", line);
    printf("the value in cPtr is %s \n", strchr(line, '\n'));

    struct  Word*       word1        = (struct Word*)malloc(sizeof(struct Word));
    struct  Word*       word2        = (struct Word*)malloc(sizeof(struct Word));
    struct  Word*       word3        = (struct Word*)malloc(sizeof(struct Word));
    char*               wordText1    =(char*)malloc(4);
    char*               wordText2    =(char*)malloc(4);
    char*               wordText3    =(char*)malloc(4);
    wordText1 = "word";
    wordText2 = "bird";
    wordText3 = "nerd";
    word1->textPtr_ = wordText1;
    word1->nextPtr_ = word2;
    word2->textPtr_ = wordText2;
    word2->nextPtr_ = word3;
    word3->textPtr_ = wordText3;
    word3->nextPtr_ = NULL;

    printCommaSeparatedList(word1);

    return(EXIT_SUCCESS);
}
