#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "Auxiliary.h"

#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

static void * myThread (void * arg);            /* thread that does the work */

int main (int argc, char *argv[])
{
    int         servSock;     /* Socket descriptor for server */
    int         clntSock;     /* Socket descriptor for client */
    pthread_t   threadID;     /* Thread ID from pthread_create() */
    bool        to_quit = false;

    parse_args (argc, argv);

    servSock = CreateTCPServerSocket(argv_port);

    while (to_quit == false)                /* run until someone indicates to quit... */
    {
        clntSock = AcceptTCPConnection(servSock);

        // TODO: create&start the thread myThread() te creeeren
        pthread_t thread;       
        // use the POSIX operation pthread_create()
        //
        // make sure that clntSock and servSock are closed at the correct locations 
        // (in particular: at those places where you don't need them any more)
        if (pthread_create (&thread, NULL,myThread, (void *)clntSock) != 0)
        {
        perror ("pthread_create(a)");
        }
        //pthread_join(thread,(void*)clntSock);
        //to_quit = true;

    }
    close (servSock);
    info ("close");
    // server stops...
	return (0);
}

static void *
myThread (void * threadArgs)
{
    // TODO: write the code to handle the client data
    // use operation HandleTCPClient()
    //  
    // Hint: use the info(), info_d(), info_s() operations to trace what happens
    //
    //clntSock = AcceptTCPConnection (servSock);
    //HandleTCPClient (clntSock);
    // Note: a call of pthread_detach() is obligatory
    int clntSock;
    clntSock= (int)threadArgs;
    HandleTCPClient (clntSock);
    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(b)");
    }
    return (NULL);
}
