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

pthread_mutex_t activeUsersMutex = PTHREAD_MUTEX_INITIALIZER;

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

	int numBroadcasts = 0; 	// The number of broadcasts that have happened since the last check for dead connections
	
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
		
		numBroadcasts ++;
		
		// After a few broadcasts check each user to see of they are still active
		if(numBroadcasts == MISSED_BROADCASTS_TO_DEACTIVATE_USER){
			int numUsers = ListCount(activeUsers);
		
			DEBUG_LOG("%s%d\n", "Num users: ", numUsers);
	
			struct ACTIVE_USER curUser;			
			
			pthread_mutex_lock(&activeUsersMutex);

			curUser = *(struct ACTIVE_USER *)ListFirst(activeUsers);
			int i;
			for(i = 0; i < numUsers-1; i++){
				time_t currentTime = time(NULL);

				time_t timestamp = curUser.timestamp;
				
				time_t difference = currentTime - timestamp;

				DEBUG_LOG("%s%ld\n", "Time diff: ", difference);
				
				// If we have not received a broadcast from them in a while, remove them
				if(difference > (BROADCAST_FREQUENCY * MISSED_BROADCASTS_TO_DEACTIVATE_USER)){
					ListRemove(activeUsers);

				// Otherwise advance in the list
				}else{

					curUser = *(struct ACTIVE_USER *)ListNext(activeUsers);
				}

				
			}
			
			pthread_mutex_unlock(&activeUsersMutex);

			numBroadcasts = 0;
		}

		sleep(BROADCAST_FREQUENCY);


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
		
		pthread_mutex_lock(&activeUsersMutex);

		// TODO: search list for duplicates and update timestamp
		// TODO: If received from self, ignore

		// add user to list of active users with timestamp
		if(ListAppend(activeUsers, &newUser) != 0){
			perror("Could not add new user");
		}
		
		pthread_mutex_unlock(&activeUsersMutex);			
		// TODO: send reply
		
	
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
