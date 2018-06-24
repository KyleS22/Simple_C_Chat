/*
* windowsChatThreads.h
* author:
*     Kyle Seidenthal
*
* date: 23-06-18
* description:
*	Windows thread function definitions for the chat program
*/

#include <windows.h>

#ifndef WINDOWS_CHAT_THREADS
#define WINDOWS_CHAT_THREADS


DWORD WINAPI windowsThreadFunc(void *data);

/*
 * Function: discoveryThread
 * -------------------------
 * A function to be run in a thread that accepts UDP broadcast packets 
 * to allow other users to discover the client.
 *
 * *args: void* arguments for WinThreads
 *
 */
DWORD WINAPI discoveryThread(void *args);

/*
 * Function: msgReceiveThread
 * --------------------------
 * A function to be run in a thread that accepts new messages from other clients.
 *
 * *args: void* arguments for WinThreads
 */
DWORD WINAPI dmsgReceiveThread(void *args);

/*
 * Function: msgSendThread
 * -----------------------
 * A function to be run in a thread that sends outgoing messages to other clients
 *
 * *args: void* arguments for WinThreads
 */
DWORD WINAPI msgSendThread(void *args);

/*
 * Function: userInputThread
 * -------------------------
 * A function to be run in a thread that accepts user input for new outgoing messages
 *
 * *args: void* arguments for WinThreads
 */
DWORD WINAPI userInputThread(void *args);

/*
 * Function: userDisplayThread
 * ---------------------------
 * A function to be run in a thread that displays new messages from other clients
 *
 * *args: void* arguments for WinThreads
 */
DWORD WINAPI userDisplayThread(void *args);


#endif // WINDOWS_CHAT_THREADS

