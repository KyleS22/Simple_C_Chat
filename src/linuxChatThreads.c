/*
* linuxChatThreads.c
* author:
*     Kyle Seidenthal
*
* date: 01-07-18
* description: Implementation of thread functions for the chat program
*/

#include "linuxChatThreads.h"
#include "debug.h"
#include "queue.h"
#include "list.h"
#include "socketHelpers.h"
#include <pthread.h>
#include <time.h>

#define DISCOVER_PORT "4950"

#define BROADCAST_FREQUENCY 10 // in seconds
#define MISSED_BROADCASTS_TO_DEACTIVATE_USER 3	// The number of broadcasts that must be missed to consider a user offline


int keepAlive = 1;

LIST *activeUsers;

/*
 * Exit the chat and clean up threads
 */
void exitChat(){
	if(keepAlive == 1){
		keepAlive = 0;
	}
}


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
	
	
		if(sendto(socketFd, username, sizeof(username), 0, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
			perror("Send");
		}

		DEBUG_LOG("%s", "Sent broadcast\n");

		sleep(BROADCAST_FREQUENCY);

		// TODO: every MISSED_BROADCASTS_TO_DEACTIVATE_USER broadcasts, remove all users from activeUsers whose timestamps are older than BROADCAST_FREQUENCY * MISSED_BROADCASTS_TO_DEACTIVATE_USER

	}

	return 0;
}


void *discoveryReceiverThread(void *args){
	// Socket stuff
	activeUsers = ListCreate();
	
	int socketFd;				// Socket descriptor for listening
	struct addrinfo *servinfo;
	int numbytes;				// Number of bytes received
	socklen_t addrSize;			// Size of the address
	struct sockaddr_storage theirAddr;	// The address to connect with
	char buf[MAXBUFLEN];			// Buffer for incoming data

	
	servinfo = NULL;

	socketFd = initializeUDPServerSocket(DISCOVER_PORT, servinfo);

	addrSize = sizeof(theirAddr);
	
	DEBUG_LOG("%s", "Listening for packets...\n");

	while(keepAlive){
		
		if((numbytes = recvfrom(socketFd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&theirAddr, &addrSize)) == -1){
			perror("recvfrom");
		}

		buf[numbytes] = '\0';

		DEBUG_LOG("%s%s\n", "Received ", buf);

		time_t currentTime = time(NULL);

		struct ACTIVE_USER newUser;		// The newly discovered user

		strcpy(newUser.username, buf);
		newUser.timestamp = currentTime;
		
		// add user to list of active users with timestamp
		if(ListAppend(activeUsers, &newUser) != 0){
			perror("Could not add new user");
		}
			
		// TODO: send reply
		
		// TODO: If received from self, ignore
	
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
