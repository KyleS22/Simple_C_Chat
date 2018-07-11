/*
* linuxChatThreads.h
* author:
*     Kyle Seidenthal
*
* date: 23-06-18
* description: 
* 	Definition of threads to use on linux machines
*/

#include <time.h>

#ifndef LINUX_CHAT_THREADS
#define LINUX_CHAT_THREADS

/*
 * Function: discoveryThread
 * -------------------------
 * A function to be run in a thread that accepts UDP broadcast packets 
 * to allow other users to discover the client.
 *
 * *args: void* arguments for pthreads
 *
 */
void *discoveryThread(void *args);


/* 
 * Function: discoveryReceiveThread
 * --------------------------------
 * A function for receiving discovery broadcast messages
 *
 * *args: void* arguments for pthreads
 */
void *discoveryReceiverThread(void *args);


/*
 * Function: msgReceiveThread
 * --------------------------
 * A function to be run in a thread that accepts new messages from other clients.
 *
 * *args: void* arguments for pthreads
 */
void *msgReceiveThread(void *args);

/*
 * Function: msgSendThread
 * -----------------------
 * A function to be run in a thread that sends outgoing messages to other clients
 *
 * *args: void* arguments for pthreads
 */
void *msgSendThread(void *args);

/*
 * Function: userInputThread
 * -------------------------
 * A function to be run in a thread that accepts user input for new outgoing messages
 *
 * *args: void* arguments for pthreads
 */
void *userInputThread(void *args);

/*
 * Function: userDisplayThread
 * ---------------------------
 * A function to be run in a thread that displays new messages from other clients
 *
 * *args: void* arguments for pthreads
 */
void *userDisplayThread(void *args);


#endif // LINUX_CHAT_THREADS
