/*-------------------------------------------------------------------------* 
*--- ---* 
*--- crazyIceCream.c ---* 
*--- ---* 
*--- ---- ---- ---- ---- ---- ---- ---- ---- ---* 
*--- ---* 
*--- Version 1a 2016 November 15 Joseph Phillips ---* 
*--- ---* 
*-------------------------------------------------------------------------*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> // For memset(), strlen() 
#include <unistd.h> // For pipe(), usleep() 
#include <signal.h> // For sigaction() #include <wait.h> // For wait()

const int 	BUFFER_LEN = 128;
int 		shouldContinue = 1;

void 		stopContinuing (int sigNum ) {
    shouldContinue = 0; 
}

int main () {  
    int 	childToParent[2];  
    pid_t 	childPid;

    // (A) Initialize 'childToParent[]' as a pipe  
    pipe(childToParent);
    printf("Parent: \"What would you like on your ice cream, sweetie?\"\n");
    childPid = fork();  // <--- (B) Replace 0 to make a child process
    if  (childPid == 0)  {    
        struct sigaction act;

        const char* cPtr;

        //  (C)  Install signal handler to do 'stopContinuing()' when receive 'SIGINT'

        struct 	sigaction	action;
        memset(&action,'\0',sizeof(action));
        action.sa_flags   = 0;
        action.sa_handler = stopContinuing;
        sigaction(SIGINT,&action,NULL);

        printf("Child \"Okay, gimme ...\"\n");
        while  (shouldContinue)    
        {
            switch  (rand() % 10) 
            {      case 0 : cPtr = "peanuts, "; break;
                   case 1 : cPtr = "caramel, "; break;
                   case 2 : cPtr = "strawberries, "; break;      
                   case 3 : cPtr = "maraschino cherries, "; break;      
                   case 4 : cPtr = "grilled onions, "; break;      
                   case 5 : cPtr = "bananas, "; break;      
                   case 6 : cPtr = "sprinkles, "; break;      
                   case 7 : cPtr = "chocolate chips, "; break;      
                   case 8 : cPtr = "whipped cream, "; break;      
                   case 9 : cPtr = "hot sauce, "; break;      
            }

            printf("Child \"%s\"\n",cPtr); 
            //  (D) Send cPtr to parent (how many bytes?)      
            write(childToParent[1],cPtr,strlen(cPtr));
            usleep(1000);    
        }

        printf("Child: \"Okay, now let me eat it!\"\n");    
        exit(EXIT_SUCCESS);  
    }
    
    char   toppingsBuffer[BUFFER_LEN];  
    char   requestBuffer[BUFFER_LEN];  
    char*  bufferEndPtr = toppingsBuffer;
    
    while  (1)  
    {
        int numBytes;

        //  (E) Receive text from child and put into 'requestBuffer'. 
        //      Also set 'numBytes' to the number of bytes received.
        read(childToParent[0],requestBuffer,BUFFER_LEN);
        numBytes = strlen(requestBuffer);
        if  ( (numBytes + (bufferEndPtr - toppingsBuffer)) >= BUFFER_LEN)      
            break;
        
        requestBuffer[numBytes] = '\0';    
        printf("Parent \"%sand?\"\n",requestBuffer);
        
        memcpy(bufferEndPtr,requestBuffer,numBytes);    
        bufferEndPtr += numBytes;    
        *bufferEndPtr = '\0';  
    }

    printf("Parent \"I have %sthat is MORE than enough!\"\n",toppingsBuffer); 
    //  (F) Tell child to stop by sending it 'SIGINT'
    kill(childPid,SIGINT);
    //  (G) Wait for child to actually stop.  
    wait();    
    return(EXIT_SUCCESS); 
}
