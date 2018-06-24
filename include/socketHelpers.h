/*
* socketHelpers.h
* author:
*     Kyle Seidenthal
*
* date: 23-06-18
* description:
* 	Functions for dealing with socket set up.
*/

#define MAXBUFLEN 150 // The most bytes to expect from a receive call

#ifndef TCP_HELPERS
#define TCP_HELPERS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

// TODO: Deal with windows stuff

/* 
 * Function: getInAddr
 * -------------------
 *
 * Get the socket address
 */
void *getInAddr(struct sockaddr *sa);

/* 
 * Function: initializeTCPServerSocket
 * ------------------------------------
 *
 * Gathers address info and binds to a port for communication with clients.
 *
 * port: The port to listen on
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 On failure
 */ 
int initializeTCPServerSocket(char port[]);

/* 
 * Function: initializeTCPClientSocket
 * -----------------------------------
 *
 * Gathers address info and binds to a port for communicating with a server
 *
 * host: The host to connect to
 * port: The port to connect to 
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 on failure
 */
int initializeTCPClientSocket(char host[], char port[]);


/* 
 * Function: initializeUDPServerSocket
 * -----------------------------------
 *
 * Gathers address info and binds to a port for communication with clients.
 *
 * port: The port to listen on
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 On failure
 */
int initializeUDPServerSocket(char port[], struct addrinfo *serverInfo);

/* 
 * Function: initializeUDPClientSocket
 * -----------------------------------
 *
 * Gathers address info and binds to a port for communicating with a server
 *
 * host: The host to connect to
 * port: The port to connect to 
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 on failure
 */
int initializeUDPClientSocket(char host[], char port[], struct addrinfo **serverInfo);

/*
 * Function: socketClose
 * ---------------------
 *
 * Wrapper for closing sockets for windows or pthreads
 */
void socketClose();

// TODO: Replace all calls to close socket with socketClose()


#endif // TCP_HELPERS

