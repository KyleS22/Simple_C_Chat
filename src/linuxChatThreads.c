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
#include "socketHelpers.h"
#include <pthread.h>

#define DISCOVER_PORT "4950"

/*
 * Discover other users on the network
 */
void *discoveryThread(void *args){
	
	// Socket stuff
	
	int socketFd;	// Socket descriptor for sending
	struct addrinfo *servinfo;	// Place to store address info

	socketFd = initializeUDPClientSocket("255.255.255.255", DISCOVER_PORT, &servinfo, 1);

	if(sendto(socketFd, "Hello World!", 12, 0, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
		perror("Send");
	}

	DEBUG_LOG("%s", "Sent broadcast\n");

	

	// TODO: LAN discovery
		

	// Find other users
	// Connect if chosen
	// pass connection details to receive and send threads
	return 0;
}


void *discoveryReceiverThread(void *args){
	// Socket stuff
	
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

	if((numbytes = recvfrom(socketFd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&theirAddr, &addrSize)) == -1){
		perror("recvfrom");
	}

	buf[numbytes] = '\0';

	DEBUG_LOG("%s%s\n", "Received ", buf);

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
