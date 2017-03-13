/*-------------------------------------------------------------------------*
 *---                                                                   ---*
 *---                          mathServer.c                             ---*
 *---                                                                   ---*
 *---    This file defines a C program that gets file-sys commands      ---*
 *---from client via a socket, executes those commands in their own     ---*
 *---threads, and returns the corresponding output back to the          ---*
 *---client.                                                            ---*
 *---                                                                   ---*
 *---  ----  ----  ---- ----  ----  ----  ----   ----                   ---*
 *---                                                                   ---*
 *---Version 1.02017 February 20Joseph Phillips                         ---*
 *---                                                                   ---*
 *-------------------------------------------------------------------------*/

//Compile with:
//$ gcc mathServer.c -o mathServer -lpthread

//---Header file inclusion---//

#include "mathClientServer.h"
#include <errno.h> 		// For perror()
#include <pthread.h> 		// For pthread_create()


//---Definition of constants:---//

#define		STD_OKAY_MSG		"Okay"

#define		STD_ERROR_MSG		"Error doing operation"

#define		STD_BYE_MSG		"Good bye!"

#define		THIS_PROGRAM_NAME	"mathServer"

#define		FILENAME_EXTENSION	".bc"

#define		OUTPUT_FILENAME		"out.txt"

#define		ERROR_FILENAME		"err.txt"

#define		CALC_PROGNAME		"/usr/bin/bc"

extern 		void*	handleClient(void* vPtr);

extern 		void* 	dirCommand();

const int	ERROR_FD= -1;


//---Definition of functions:---//



//  PURPOSE:  To run the server by 'accept()'-ing client requests from
//'listenFd' and doing them.
void		doServer(int	listenFd
			)
{
  //  I.  Application validity check:

  //  II.  Server clients:
  pthread_t		threadId;
  pthread_attr_t	threadAttr;
  int			threadCount= 0;
  int* 			iPtr;

  // YOUR CODE HERE

  listen(listenFd,5);  

//  pthread_create(&threadId,NULL,mathClient,NULL);
  pthread_attr_init(&threadAttr);
  while (1)  {
    printf("pre connectDesc \n");
    int  conDesc = accept(listenFd,NULL,NULL);    
    printf("connectionDescriptor = %d\n",conDesc);
    if (conDesc < 0) {
      perror("Error on accept attempt\n");
      exit(EXIT_FAILURE);
    }      

    printf("doing things in doServer");

    iPtr = (int*)calloc(2,sizeof(int*));
    iPtr[0] = conDesc;
    iPtr[1] = threadCount;
    printf("In doServer, iPtr[0] = %d, and iPtr[1] = %d \n",iPtr[0], iPtr[1]);
    threadCount++;
    printf("threadcount after ++ing it = %d\n", threadCount);
    

    pthread_attr_setdetachstate(&threadAttr,PTHREAD_CREATE_DETACHED);
    pthread_create(&threadId,&threadAttr,handleClient,(void*)iPtr);

    
  }    
}

void* 	handleClient(void* vPtr) {
  int* iPtr 		= (int*)vPtr;
  int* fd	 	= &iPtr[0];
  int* threadCount	= &iPtr[1];
  printf("iPtr[0] (conDescriptor) = %d \n",*fd);
  printf("iPtr[0] (conDesc again) = %d \n",*fd);
  printf("iPtr[1] (threadcount)   = %d \n",*threadCount);

  free(vPtr);

  //  II.B.  Read command:
  char		buffer[BUFFER_LEN];
  char		command;
  int		fileNum;
  char		text[BUFFER_LEN];
  int 		shouldContinue	= 1;

  while  (shouldContinue)
  {
    memset(buffer,'\0',BUFFER_LEN);
    memset(text  ,'\0',BUFFER_LEN);
    printf("inHandleClient, before the read, fd = %d \n",*fd);
    read(fd,buffer,BUFFER_LEN);
    printf("Thread %d received: %s\n",*threadCount,buffer);
    printf("inHandleClient, before sscanf \n");
    printf("command = %s, fileNum = %d, text = %s \n",&command,fileNum,text);
    sscanf(buffer,"%c %d \"%[^\"]\"",&command,&fileNum,text);

    // YOUR CODE HERE
//    dirCommand();
    printf("buffer = %s \n",buffer);
    printf("text = %s \n",text);
    printf("Command = %s \n",&command);
    shouldContinue=0;
    dirCommand();
//    if (&command == "DIR_CMD_CHAR") {
//      printf("entered DIR_CMD_CHAR \n");
//    }
  } 
}

void* 		dirCommand() {
  DIR* 			dirPtr = opendir(".");

  if (dirPtr == NULL) {
    fprintf(stderr,STD_ERROR_MSG);
    exit(EXIT_FAILURE);
  }

  struct  dirent*       entryPtr;
  char 			buffer[BUFFER_LEN];
  char*			filename;
  printf("in dirCommand, about to enter while \n");
  while ( (entryPtr = readdir(dirPtr)) != NULL ) {
    filename = entryPtr->d_name;
    strncat(buffer,filename,BUFFER_LEN);
    strncat(buffer,"\n",BUFFER_LEN); 
//    printf("filename = %s \n",filename);
//    strcat(*filename,"\n");
//    strcat(buffer, &filename);
    printf("%s\n",buffer);
  }
  closedir(dirPtr);
}

void* 		readCommand(int 	fileNum ) {
    char 	fileName[BUFFER_LEN];
    snprintf(fileName,BUFFER_LEN,"%d%s",fileNum,FILENAME_EXTENSION);

    char 	buffer[BUFFER_LEN];
    int 	fd = open(fileName,O_RDONLY,0440); //

    if (fd <= -1) {
        fprintf(stderr,STD_ERROR_MSG);
    }

    read(fd,buffer,BUFFER_LEN);
    strcat(buffer,"\0");
    write(fd,buffer,strlen(buffer));
    close(fd);
}


//void* 		writeCommand(int 	fileNum
//			     char	text) 
//{
        
//}

//  PURPOSE:  To decide a port number, either from the command line arguments
//'argc' and 'argv[]', or by asking the user.  Returns port number.
int		getPortNum(	int	argc,
 				char*	argv[]
			  )
{
  //  I.  Application validity check:

  //  II.  Get listening socket:
  int	portNum;

  if  (argc >= 2)
    portNum= strtol(argv[1],NULL,0);
  else
  {
    char 	buffer[BUFFER_LEN];

    printf("Port number to monopolize? ");
    fgets(buffer,BUFFER_LEN,stdin);
    portNum = strtol(buffer,NULL,0);
  }

  //  III.  Finished:  
  return(portNum);
}


//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//to the OS telling this server when a client process has connect()-ed
//to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor (int	port
					)
{
  //  I.  Application validity check:

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  II.A.  Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
        	SOCK_STREAM, // Reliable TCP
	        0);

  if  (socketDescriptor < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.  Attempt to bind 'socketDescriptor' to 'port':
  //  II.B.1.  We'll fill in this datastruct
  struct sockaddr_in socketInfo;

  //  II.B.2.  Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));

  //  II.B.3.  Use TCP/IP:
  socketInfo.sin_family = AF_INET;

  //  II.B.4.  Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  //  II.B.5.  Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;

  //  II.B.6.  Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
    		   (struct sockaddr*)&socketInfo,
     		   sizeof(socketInfo)
    		   );

  if  (status < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.6.  Set OS queue length:
  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor);
}


int  	main 	(int 	argc,
  		 char*	argv[]
	    	)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int 	   port= getPortNum(argc,argv);
  int      listenFd= getServerFileDescriptor(port);
  int      status= EXIT_FAILURE;

  if  (listenFd >= 0)
  {
    doServer(listenFd);
    close(listenFd);
    status= EXIT_SUCCESS;
  }

  //  III.  Finished:
  return(status);
}
