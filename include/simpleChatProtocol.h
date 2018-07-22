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

#define DISCOVER_PORT "4950"

#define BROADCAST_FREQUENCY 10 // in seconds
#define MISSED_BROADCASTS_TO_DEACTIVATE_USER 3	// The number of broadcasts that must be missed to consider a user offline


struct ACTIVE_USER{
	char username[20];
	time_t timestamp;
	// TODO: add ip address	
};


extern int keepAlive; // Keep all threads running
extern int numBroadcasts; // The number of broadcasts we have sent
extern LIST *activeUsers;

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
// TODO: Define functions


#endif // SIMPLE_CHAT_PROTOCOL
