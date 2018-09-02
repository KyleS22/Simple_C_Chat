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
pthread_mutex_t outgoingMessageMutex = PTHREAD_MUTEX_INITIALIZER;

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

	//char *username;

	//username = (char *) args;

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

		pthread_mutex_lock(&activeUsersMutex);
		
		if(addNewUserToUserList(newUser) == -1){
			DEBUG_ERR("%s", "The new user was not added to the list.");
		}
	
		pthread_mutex_unlock(&activeUsersMutex);					
	
	}

	return 0;

}

void *acceptChatConnectionsThread(void *args){
	startChatServer();

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
	
		
	while(keepAlive){
		
		if(messagesToSend() == 1){
			pthread_mutex_lock(&outgoingMessageMutex);
			sendNextMessage();
			pthread_mutex_unlock(&outgoingMessageMutex);
		}
	}

	return 0;
	
}

/*
 * Get input from the user and prepare to send
 */
void *userInputThread(void *args){

	int menu = 1;
	int connectedToUser = 1;
	int userChoice;
	struct ACTIVE_USER *selectedUser;
	char userInput[288];

	while(menu){
		if(displayActiveUsers() != 0){
			continue;
		}
		printf("Enter the number of the user you wish to connect with or -1 to refresh: \n");
		scanf("%d", &userChoice);
		
		DEBUG_ERR("USER CHOIDE: %d", userChoice);
		
		if(userChoice == -1){
			continue;
		}

		pthread_mutex_lock(&activeUsersMutex);
		selectedUser = selectChatUser(userChoice);
		pthread_mutex_unlock(&activeUsersMutex);

		printf("Connecting to %s...\n", selectedUser->username);

		// TODO: Need to establish client connection

		if(selectedUser != NULL){
			// Connect to the selected user
			if(connectToUser(selectedUser->thierAddr) == 0){
				connectedToUser = 1;
			} else {
				printf("Unable to connect...");
			}
			
			// We are in chat mode
			printf("You are now connected to %s Type messages and press enter to send.\nEnter \\q to quit.\n", selectedUser->username);

			while(connectedToUser){
				fgets(userInput, sizeof userInput, stdin);
				DEBUG_LOG("User Input: %s\n", userInput);

				if((strlen(userInput) > 0) && (userInput[strlen(userInput) - 1] == '\n')){
					userInput[strlen(userInput) - 1] = '\0';
				}

				if(strcmp(userInput, "\\q") == 0){
					printf("Disconnecting from %s...\n", selectedUser->username);
					connectedToUser = 0;
				}else{
					//Add message to outgoing message queue
					pthread_mutex_lock(&outgoingMessageMutex);

					addOutgoingMessage(userInput);

					pthread_mutex_unlock(&outgoingMessageMutex);
				}
			}
		}
	}

	
	
	return 0;
}

/*
 * Display info and incoming messages to the user
 */
void *userDisplayThread(void *args){

	// TODO: Display info and messages to the user
	return 0;
}	
