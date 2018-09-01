/*
* simpleChatProtocol.h
* author:
*     Kyle Seidenthal
*
* date: 23-06-18
* description:
* 	Defines the functions used to control the simple chat program.
*/

#ifndef SIMPLE_CHAT_PROTOCOL
#define SIMPLE_CHAT_PROTOCOL

#include "queue.h"
#include "list.h"
#include "socketHelpers.h"
#include <time.h>

#define DISCOVER_PORT "4951"
#define CHAT_PORT "4952"
#define LISTEN_PORT "4953"

#define BROADCAST_FREQUENCY 10 // in seconds
#define MISSED_BROADCASTS_TO_DEACTIVATE_USER 3	// The number of broadcasts that must be missed to consider a user offline


struct ACTIVE_USER{
	char username[20];
	time_t timestamp;
	struct sockaddr_storage thierAddr;
	socklen_t addrSize;
};


extern int keepAlive; // Keep all threads running
extern int numBroadcasts; // The number of broadcasts we have sent
extern LIST *activeUsers;
extern QUEUE *outgoingMessages;

/*
 * Function: exitChat
 * ------------------
 * A function that signals all running threads to clean up and exit the program
 */
void exitChat();


/*
 * Function: sendDiscoveryBroadcast
 * --------------------------------
 *
 * Send out a UDP broadcast to the network to allow other users to know we are on-line
 *
 * socketFd: Socket file descriptor for sending the broadcast
 * servinfo: A place to store address info
 * username: The username to send to other users
 */
int sendDiscoveryBroadcast(int socketFd, struct addrinfo *servinfo, char *username);

/*
 * Functin: checkInactiveUsers
 * -----------------------------
 *
 * Check all users that have been logged to see if they have become inactive
 */
int checkInactiveUsers(); 


/*
 * Function: receiveNewUserBroadcast
 * ---------------------------------
 *
 * Receive a UDP broadcast from other users on the network
 *
 * socketFd: The socket file descriptor for listening on
 *
 * return: A new ACTIVE_USER struct with the new user's info
 */
struct ACTIVE_USER *receiveNewUserBroadcast(int socketFd);

/*
 * Function addNewUserToUserList
 * -----------------------------
 *
 * Add the given user to the list of active users.  If the user already exists
 * in the list, update their timestamp.
 *
 * newUser: The new user struct with info about the user
 *
 * return: 0 on success
 * 	   -1 if the user could not be added to the list
 */
int addNewUserToUserList(struct ACTIVE_USER *newUser);


/*
 * Function selectChatUser
 * -----------------------
 * 
 * Given an integer position of an active user in the list, return that struct from the list
 * 
 * selectedUser: The index in the list of the desired user
 * 
 * return: The selected user
 * 		   NULL on failure 
 */
struct ACTIVE_USER *selectChatUser(int selectedUser);

/**
 * Function displayActiveUsers
 * ---------------------------
 * 
 * Print the list of currently available users.
 * 
 * Return: 0 on success
 * 		   -1 if the list is empty
 */
int displayActiveUsers();

/**
 * Function addOutgoingMessage
 * ----------------------------
 * 
 * Add a string to the outgoing message queue
 * 
 * Return: 0 on success
 * 		   -1 if the message was not added
 */
int addOutgoingMessage(char message[]);


/**
 * Function messagesToSend
 * -----------------------
 * 
 * Check to see if there are messages in the outgoing queue
 * 
 * Return: 0 if there are no messages to send
 * 		   1 if there are messages to send
 */
int messagesToSend();

/**
 * Function sendNextMessage
 * ------------------------
 * 
 * Send the next message in the outgoing message queue
 * 
 * Return 0 if successful
 */
int sendNextMessage();


/**
 * Function connectToUser
 * ----------------------
 * 
 * Create a TCP connection with the given user
 * Param theirAddr: A sockaddr_storage type containing the address to connect with
 * 
 * Return: 0 on success
 * 		   -1 on failure
 * 
 */ 
int connectToUser(struct sockaddr_storage theirAddr);

/**
 * 	Function startChatServer
 *  ------------------------
 * 
 * Start a listener connection to accept chat requests from other users.
 * 
 * Return: 0 when the server is terminated
 */
int startChatServer();

#endif // SIMPLE_CHAT_PROTOCOL
