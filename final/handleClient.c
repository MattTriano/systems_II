void handleClient (int toClientFd) 
{  
    char buffer[BUFFER_LEN];  
    int fileSize;  
    DIR* dirPtr;

    // (A) YOUR CODE HERE
    read(toClientFd,&fileSize,sizeof(int));
    fileSize = ntohl(fileSize);
    dirPtr = opendir(".");
    if  (dirPtr != NULL)  
    {
        struct dirent* dirEntryPtr;
        struct stat statBuf;

        while  ( (dirEntryPtr = readdir(dirPtr)) != NULL )    ///* (B) YOUR CODE IN WHILE CONDITION */
        {
            // (C) YOUR CODE HERE
            stat(dirEntryPtr->d_name,&statBuf); // 

            if  (  S_ISREG(statBuf.st_mode) && (statBuf.st_size <= fileSize))      // (D) YOUR CODE IN IF CONDITION
            {
                // (E) YOUR CODE HERE      
                snprintf(buffer,BUFFER_LEN,"%s",dirEntryPtr->d_name);
                write(toClientFd,buffer,BUFFER_LEN);
            }
        }
    }
    // (F) YOUR CODE HERE
    closedir(dirPtr);
    snprintf(buffer,BUFFER_LEN,"%s",END_OF_LIST_STRING);
    write(toClientFd,buffer,BUFFER_LEN);
}
