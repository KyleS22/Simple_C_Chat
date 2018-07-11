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


int keepAlive = 1;  // Keep the threads alive
int numBroadcasts = 0;	// The number of broadcasts that have been sent

LIST *activeUsers;

/*
 * Exit the chat and clean up threads
 */
void exitChat(){
	if(keepAlive == 1){
		keepAlive = 0;
	}
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
	
		struct ACTIVE_USER curUser;			
			
		curUser = *(struct ACTIVE_USER *)ListFirst(activeUsers);
		
		int i;
		for(i = 0; i < numUsers; i++){

			DEBUG_LOG("%s%s\n", "Cur User: ", curUser.username);
			time_t currentTime = time(NULL);
			DEBUG_LOG("%s%ld\n", "Current Time: ", currentTime);
			
			// TODO: this timestamp is wrong
			time_t timestamp = curUser.timestamp;
			DEBUG_LOG("%s%ld\n", "User Timestamp: ", timestamp);				
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
			

		numBroadcasts = 0;

	}

	return 0;
}


struct ACTIVE_USER receiveNewUserBroadcast(int socketFd){
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
	
	struct ACTIVE_USER newUser;

	strcpy(newUser.username, buf);
	newUser.timestamp = currentTime;
	
	// TODO: get IP
	
	return newUser;
}

int addNewUserToUserList(struct ACTIVE_USER newUser){
	// TODO: search list for duplicates and update timestamp
	// TODO: if received from self, ignore
	
	// add er tp list of active users with timestamp
	
	DEBUG_LOG("%s%ld\n", "New user timestamp: ", newUser.timestamp);
		
	if(ListAppend(activeUsers, &newUser) != 0){
		return -1;
	}

	return 0;
	
}
