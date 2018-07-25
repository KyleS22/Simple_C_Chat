/*
* linuxChatThreads.c
* author:
*     Kyle Seidenthal
*
* date: 01-07-18
* description: Implementation of thread functions for the chat program
*/

#include "linuxChatThreads.h"
#include "simpleChatProtocol.h"
#include "debug.h"
#include "queue.h"
#include "list.h"
#include "socketHelpers.h"
#include <pthread.h>
#include <time.h>

pthread_mutex_t activeUsersMutex = PTHREAD_MUTEX_INITIALIZER;


/*
 * Discover other users on the network
 */
void *discoveryThread(void *args){
	
	char *username;
	
	username = (char *) args;

	DEBUG_LOG("%s%s\n", "Username is: ", username);
		
	// Socket stuff
	
	int socketFd;	// Socket descriptor for sending
	struct addrinfo *servinfo;	// Place to store address info

	socketFd = initializeUDPClientSocket("255.255.255.255", DISCOVER_PORT, &servinfo, 1);

	// Repeat the broadcast at BROADCAST_FREQUENCY
	while(keepAlive){	
		sendDiscoveryBroadcast(socketFd, servinfo, username);	
		
		pthread_mutex_lock(&activeUsersMutex);
		checkInactiveUsers();
		pthread_mutex_unlock(&activeUsersMutex);

		sleep(BROADCAST_FREQUENCY);
	}

	return 0;
}


void *discoveryReceiverThread(void *args){

	char *username;

	username = (char *) args;

	// Socket stuff
	activeUsers = ListCreate();
	
	int socketFd;				// Socket descriptor for listening
	struct addrinfo *servinfo;

	servinfo = NULL;

	socketFd = initializeUDPServerSocket(DISCOVER_PORT, servinfo);

	
	DEBUG_LOG("%s", "Listening for packets...\n");

	while(keepAlive){
		struct ACTIVE_USER *newUser;
		newUser = receiveNewUserBroadcast(socketFd);

		DEBUG_LOG("%s%s\n", "New Username: ", newUser->username);
		DEBUG_LOG("%s%ld\n", "New User Time Stamp: ", newUser->timestamp);	
		pthread_mutex_lock(&activeUsersMutex);
		
		addNewUserToUserList(newUser);
	
		pthread_mutex_unlock(&activeUsersMutex);					
	
	}

	return 0;

}

/*
 * Receive incoming messages from connected users
 */
void *msgReceiveThread(void *args){

	// TODO: Receive incoming messages from a TCP socket
	
	

	return 0;

}

/*
 * Send messages to connected users
 */
void *msgSendThread(void *args){
	// TODO: Send outgoing messages to a TCP socket
	
	return 0;
	
}

/*
 * Get input from the user and prepare to send
 */
void *userInputThread(void *args){

	// TODO: Get user input
	
	return 0;
}

/*
 * Display info and incoming messages to the user
 */
void *userDisplayThread(void *args){

	// TODO: Display info and messages to the user
	return 0;
}	
