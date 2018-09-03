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
#include <sys/select.h>

pthread_mutex_t activeUsersMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t outgoingMessageMutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Discover other users on the network
 */
void *discoveryThread(void *args){
	
	char *username;
	
	username = (char *) args;
		
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

		char host[INET6_ADDRSTRLEN];

		struct sockaddr_storage theirAddr = newUser->thierAddr;

		inet_ntop(theirAddr.ss_family,
			getInAddr((struct sockaddr *)&theirAddr),
			host, sizeof(host));

		DEBUG_LOG("RECEIVED IP: %s \n\n", host);

		// IGNORE connection from self
		if(strcmp(newUser->username, username) == 0){
			continue;
		}		

		pthread_mutex_lock(&activeUsersMutex);
		
		if(addNewUserToUserList(newUser) == -1){
			DEBUG_ERR("%s", "The new user was not added to the list.");
		}
	
		pthread_mutex_unlock(&activeUsersMutex);					
	
	}

	return 0;

}

void *acceptChatConnectionsThread(void *args){
	
	while(keepAlive){
		if(gotConnection == 0){
			gotConnection = startChatServer();
		}
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
	char userChoiceChar[1];
	int userChoice = -1;
	struct ACTIVE_USER *selectedUser;
	char userInput[288];


	while(keepAlive){
		if(menu){
			pthread_mutex_lock(&activeUsersMutex);
			if(displayActiveUsers() != 0){
				pthread_mutex_unlock(&activeUsersMutex);
				continue;
			}
			pthread_mutex_unlock(&activeUsersMutex);
			
			printf("Enter the number of the user you wish to connect with or -1 to refresh: \n");

			//fgets(userChoiceChar, sizeof userChoiceChar, stdin);
			scanf("%s", userChoiceChar);
			DEBUG_LOG("FGETS %s\n", userChoiceChar);

			if(gotConnection == 1){
				DEBUG_LOG("%s\n", "Got new connection, input");
				if(strcmp(userChoiceChar, "y") == 0) {
					printf("Accepting connection from user\n");
					menu = 0;
					connectedToUser = 1;
					continue;
				} else {
					closeChatConnection();
					continue;
				}
			}

			userChoice = atoi(userChoiceChar);
			DEBUG_LOG("USER CHOICE: %d", userChoice);

			if(userChoice == -1){
				continue;
			}

			pthread_mutex_lock(&activeUsersMutex);
			selectedUser = selectChatUser(userChoice);
			pthread_mutex_unlock(&activeUsersMutex);

			printf("Connecting to %s...\n", selectedUser->username);

			if(selectedUser != NULL){
				// Connect to the selected user
				if(connectToUser(selectedUser->thierAddr) == 0){
					connectedToUser = 1;
					menu = 0;
					
				} else {
					printf("Unable to connect...");
					continue;
				}
				
				// We are in chat mode
				printf("You are now connected to %s Type messages and press enter to send.\nEnter \\q to quit.\n", selectedUser->username);
				
			}
		

			
		} else if(connectedToUser) {

				fgets(userInput, sizeof userInput, stdin);
				if((strlen(userInput) > 0) && (userInput[strlen(userInput) - 1] == '\n')){
					userInput[strlen(userInput) - 1] = '\0';
				}

				if(strcmp(userInput, "\\q") == 0){
					printf("Disconnecting from %s...\n", selectedUser->username);
					connectedToUser = 0;
					menu = 1;
					gotConnection = 0;
				}else{
					//Add message to outgoing message queue
					pthread_mutex_lock(&outgoingMessageMutex);

					addOutgoingMessage(userInput);

					pthread_mutex_unlock(&outgoingMessageMutex);
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
