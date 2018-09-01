/*
* simpleChatProtocol.c
* author:
*     Kyle Seidenthal
*
* date: 07-07-18
* description:
*/

#include "simpleChatProtocol.h"
#include "debug.h"
#include "queue.h"
#include "list.h"
#include "socketHelpers.h"
#include <time.h>
#include <stdio.h>


int keepAlive = 1;  // Keep the threads alive
int numBroadcasts = 0;	// The number of broadcasts that have been sent

int chatSocketFD; // Socket descriptor for chatting with other users
int listenSocketFD; // Socket to listen for new connections on

int acceptingConnections = 1;	// Whether we are currently accepting new connectin requests

LIST *activeUsers;
QUEUE *outgoingMessages;

/*
* Free list items
*/
void itemFree(void* itemToBeFreed){
	free(itemToBeFreed);
}

int comparator(void *item, void *comparisonArg){
	if(strcmp(((struct ACTIVE_USER *)item)->username, ((struct ACTIVE_USER *)comparisonArg)->username) == 0){
		DEBUG_LOG("%s", "They are the same!\n");
		return 1;
	}else{
		DEBUG_LOG("%s", "They are different\n");
		return 0;
	}
}

/*
 * Exit the chat and clean up threads
 */
void exitChat(){
	if(keepAlive == 1){
		keepAlive = 0;
	}

	if(acceptingConnections == 1) {
		acceptingConnections = 0;
	}

	ListFree(activeUsers, itemFree);
	ListFree(outgoingMessages->list, itemFree);
}


int sendDiscoveryBroadcast(int socketFd, struct addrinfo *servinfo, char *username){
	if(sendto(socketFd, username, sizeof(username), 0, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
		perror("send");
	}
	
	DEBUG_LOG("%s", "Sent broadcast\n");
	
	numBroadcasts ++;

	return 0;
}

int checkInactiveUsers(){
	if(numBroadcasts == MISSED_BROADCASTS_TO_DEACTIVATE_USER){
		int numUsers = ListCount(activeUsers);
		
		DEBUG_LOG("%s%d\n", "Num users: ", numUsers);
	
		struct ACTIVE_USER *curUser = (struct ACTIVE_USER *)ListFirst(activeUsers);
		
		int i;
		for(i = 0; i < numUsers; i++){

			time_t currentTime = time(NULL);

			time_t timestamp = (time_t)curUser->timestamp;
			
			time_t difference = currentTime - timestamp;

				
			// If we have not received a broadcast from them in a while, remove them
			if(difference > (BROADCAST_FREQUENCY * MISSED_BROADCASTS_TO_DEACTIVATE_USER)){
				ListRemove(activeUsers);

			// Otherwise advance in the list
			}else{

				curUser = (struct ACTIVE_USER *)ListNext(activeUsers);
			}

				
		}
			

		numBroadcasts = 0;

	}

	return 0;
}


struct ACTIVE_USER *receiveNewUserBroadcast(int socketFd){
	int numbytes;				// Number of bytes 
	socklen_t addrSize;			// Size of the address
	struct sockaddr_storage theirAddr;	// The address to connect with
	char buf[MAXBUFLEN];			// Buffer for incoming data

	addrSize = sizeof(theirAddr);

	if((numbytes = recvfrom(socketFd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&theirAddr, &addrSize)) == -1){
		perror("recvfrom");
	}

	buf[numbytes] = '\0';

	DEBUG_LOG("%s%s\n", "Received ", buf);
	
	time_t currentTime = time(NULL);
	DEBUG_LOG("%s%ld\n", "Current time: ", currentTime);
	
	struct ACTIVE_USER *newUser = malloc(sizeof(struct ACTIVE_USER));

	strcpy(newUser->username, buf);
	newUser->timestamp = currentTime;
	newUser->thierAddr = theirAddr;
	newUser->addrSize = addrSize;
	
	return newUser;
}

int addNewUserToUserList(struct ACTIVE_USER *newUser){

	// TODO: if received from self, ignore
	// Search list for duplicates and update timestamp
	void* searchItem =  NULL;
	
	if(ListCount(activeUsers) > 0){
		ListFirst(activeUsers);
		searchItem = ListSearch(activeUsers, *comparator, newUser);
	}

	
	if(searchItem == NULL){
		DEBUG_LOG("%s%ld\n", "New user timestamp: ", newUser->timestamp);
		
		struct ACTIVE_USER userForList;
		strcpy(userForList.username, newUser->username);
		userForList.timestamp = newUser->timestamp;
		userForList.thierAddr = newUser->thierAddr;
		userForList.addrSize = newUser->addrSize;

		if(ListAppend(activeUsers, &userForList) != 0){
			DEBUG_ERR("%s\n", "Problem adding new user");
			return -1;
		}
		
		free(newUser);
		return 0;

	} else {
		// We need to update the timestamp

		DEBUG_LOG("%s%ld\n\n", "Old timestamp: ", ((struct ACTIVE_USER*)searchItem)->timestamp);

		memcpy(&((struct ACTIVE_USER *)ListCurr(activeUsers))->timestamp, &newUser->timestamp, sizeof newUser->timestamp);

		DEBUG_LOG("%s%ld\n\n", "Updated timestamp: ", ((struct ACTIVE_USER*)searchItem)->timestamp);

		return 0;
	}

	return -1;
}

int displayActiveUsers(){
	if(activeUsers == NULL){
		return -1;
	}

	// Loop through list and display user names for user to select
	if(ListCount(activeUsers) <= 0){
		return -1;
	}

	struct ACTIVE_USER *curUser = (struct ACTIVE_USER *)ListFirst(activeUsers);

	int i;
	for(i = 0; i < ListCount(activeUsers); i++){
		printf("%i - %s\n", (i), curUser->username);
		curUser = (struct ACTIVE_USER *)ListNext(activeUsers);
	}


	return 0;
}

struct ACTIVE_USER *selectChatUser(int selection){
	struct ACTIVE_USER *selectedUser = (struct ACTIVE_USER *)ListFirst(activeUsers);
	
	// Take user input and return list item so we can connect

	int i = 0;
	while(i != selection){
		i ++;
		selectedUser = (struct ACTIVE_USER *)ListNext(activeUsers);
	}

	return selectedUser;
}


int addOutgoingMessage(char message[]){
	if (outgoingMessages == NULL){
		outgoingMessages = QueueCreate();
	}

	if(Enqueue(outgoingMessages, &message) == -1){
		DEBUG_ERR("%s\n", "There was an error adding the message to the queue.");
	}

	return 0;
}


int messagesToSend(){

	if(outgoingMessages == NULL) {
		return 0;
	}

	if(QueueCount(outgoingMessages) > 0) {
		return 1;
	} else {
		return 0;
	}
}

int sendNextMessage(){
	char* messageToSend = (char*) Dequeue(outgoingMessages);
	
	if(send(chatSocketFD, messageToSend, sizeof messageToSend, 0) == -1){
		perror("Failed to send message.");
	}

	return 0;
}

int connectToUser(struct sockaddr_storage theirAddr) {
	char host[INET6_ADDRSTRLEN];

	inet_ntop(theirAddr.ss_family,
		getInAddr((struct sockaddr *)&theirAddr),
		host, sizeof(host));

	DEBUG_LOG("Connecting to IP: %s \n\n", host);

	// Create a socket for communitcations

	chatSocketFD = initializeTCPClientSocket(host, LISTEN_PORT);

	if(chatSocketFD == -1){
		return -1;
	}

	return 0;	
}

int startChatServer(){
	socklen_t sinSize;
	struct sockaddr_storage theirAddr;
	char addressString[INET6_ADDRSTRLEN];

	char choice[1];

	listenSocketFD = initializeTCPServerSocket(LISTEN_PORT);

	while(keepAlive == 1) {
		while(acceptingConnections == 1) {
			chatSocketFD = accept(listenSocketFD, (struct sockaddr *)&theirAddr, &sinSize);

			if(chatSocketFD == -1) {
				perror("accept");
				continue;
			}

			inet_ntop(theirAddr.ss_family,
				getInAddr((struct sockaddr *)&theirAddr),
				addressString, sizeof addressString);

			DEBUG_LOG("Server: got connection from %s\n", addressString);

			printf("Received connection.  Would you like to connect? (y/n) ");
			fgets(choice, sizeof choice, stdin);

			if(strcmp(choice, "y") == 0) {
				acceptingConnections = 0;
				// TODO: This needs to abort the userInput thread so we can get into chat mode
			}
		}
	}

	socketClose(listenSocketFD);
	socketClose(chatSocketFD);

	return 0;
}