/*
* socketHelpers.c
* author:
*     Kyle Seidenthal
*
* date: 01-07-18
* description: Implementation of socket functions
*/


#include "socketHelpers.h"
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

#define BACKLOG 5  // How many connections will we hold?

/* Get the socket address 
 *
 * sa:  A sockaddr struct for the address 
 */
void *getInAddr(struct sockaddr *sa){
        if(sa->sa_family == AF_INET){
                return &(((struct sockaddr_in*)sa)->sin_addr);
        }
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* Gathers address info and binds to a port for communication with clients.
 *
 * port: The port to listen on
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 On failure
 */
int initializeTCPServerSocket(char port[]){
        int status;                     // To catch errors
        int socketFd;                   // File descriptor for the socket
        
        struct addrinfo hints;          // Struct to hold server info
        struct addrinfo *servinfo;      // Place to store results from getaddrinfo
        struct addrinfo *p;             // For finfing a result to bind to 
        
        memset(&hints, 0, sizeof hints);        // Make sure hints is empty
        hints.ai_family = AF_UNSPEC;            // IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;        // Use TCP stream sockets
        hints.ai_flags = AI_PASSIVE;            // Use my IP
        
        // Get the info in servinfo
        if((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0){
                fprintf(stderr, "getadrinfo errir: %s\n", gai_strerror(status));
                exit(1);
        }       
        
        // loop through our results to find a valid socket to bind to
        for(p = servinfo; p != NULL; p = p->ai_next){
                // Try to get the socket descriptor of the first result
                if((socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
                        perror("Server: Socket");
                        continue;
                }       
                
                // Try to bind to the socket
                if(bind(socketFd, p->ai_addr, p->ai_addrlen) == -1){
                        close(socketFd);
                        perror("Server: Bind");
                        continue;
                }       
               
                break;
        }       
        
        freeaddrinfo(servinfo); // Obliterate the linked list of results
        
        // If we ran out of results and did not bind, that would be bad
        if(p == NULL){
                fprintf(stderr, "Server: Failed to bind\n");
                exit(1);
        }       
        
        if(listen(socketFd, BACKLOG) == -1){
                perror("listen");
                exit(1);
        }       
        
        
        return socketFd;
}       


/* Gathers address info and binds to a port for communicating with a server
 *
 * host: The host to connect to
 * port: The port to connect to 
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 on failure
 */ 
int initializeTCPClientSocket(char host[], char port[]){
        int status;                     // To catch errors
        int socketFd;                   // File descriptor for the socket
        
        struct addrinfo hints;          // Struct to hold server info
        struct addrinfo *servinfo;      // Place to store results from getaddrinfo
        struct addrinfo *p;             // For finding a result to bind to 
        
        char addressString[INET6_ADDRSTRLEN];
        
        memset(&hints, 0, sizeof hints);        // Make sure hints is empty
        hints.ai_family = AF_UNSPEC;            // IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;        // Use TCP stream sockets
        
        // Get the info in servinfo
        if((status = getaddrinfo(host, port, &hints, &servinfo)) != 0){
                fprintf(stderr, "getadrinfo errir: %s\n", gai_strerror(status));
                exit(1);
        }
        
        // loop through our results to find a valid socket to bind to
        for(p = servinfo; p != NULL; p = p->ai_next){
                // Try to get the socket descriptor of the first result
                if((socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
                        perror("Server: Socket");
         continue;
                }       
                
                // Try to connect to the socket
                if(connect(socketFd, p->ai_addr, p->ai_addrlen) == -1){
                        close(socketFd);
                        perror("Server: Bind");
                        continue;
                }       
                
                break;
        }       
        
  
        // If we ran out of results and did not connect, that would be bad
        if(p == NULL){
                fprintf(stderr, "Client: Failed to connect\n");
                exit(1);
        }       
        
        inet_ntop(p->ai_family, getInAddr((struct sockaddr *)p->ai_addr), addressString, sizeof addressString);
        
        freeaddrinfo(servinfo); // Obliterate the linked list of results
        
        return socketFd;
}       


/* Gathers address info and binds to a port for communication with clients.
 *
 * port: The port to listen on
 *
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 On failure
 */
int initializeUDPServerSocket(char port[], struct addrinfo *serverInfo){
        int status;                     // To catch errors 
        int socketFd;                   // File descriptor for the socket
        
        struct addrinfo hints;          // Struct to hold server info
        struct addrinfo *servinfo;      // Place to store results from getaddrinfo
        struct addrinfo *p;             // For finding a result to bind to 
        
        memset(&hints, 0, sizeof hints);        // Make sure hints is empty
        hints.ai_family = AF_UNSPEC;            // IPv4 or IPv6
        hints.ai_socktype = SOCK_DGRAM; // Use UDP datagram sockets
        hints.ai_flags = AI_PASSIVE;            // Use my IP
        
        // Get the info in servinfo
        if((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0){
                fprintf(stderr, "getadrinfo errir: %s\n", gai_strerror(status));
                exit(1);
        }       
        
        // loop through our results to find a valid socket to bind to
        for(p = servinfo; p != NULL; p = p->ai_next){
                // Try to get the socket descriptor of the first result
                if((socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
                        perror("Server: Socket");
                        continue;
                }       
                
                // Try to bind to the socket
                if(bind(socketFd, p->ai_addr, p->ai_addrlen) == -1){
                        close(socketFd);
                        perror("Server: Bind");
                        continue;
                }       
                
                break;
        }       
        
        freeaddrinfo(servinfo); // Obliterate the linked list of results
        
        // If we ran out of results and did not bind, that would be bad
        if(p == NULL){
                fprintf(stderr, "Server: Failed to bind\n");
                exit(1);
        }       
        
        
        serverInfo = p;
        
        return socketFd;
}       


/* Gathers address info and binds to a port for communicating with a server
 *
 * host: The host to connect to
 * port: The port to connect to 
 * serverInfo: A pointer to an addrinfo struct to store the connection info in
 * broadcast: A boolean determining whether the socket may broadcast
 * Return:
 *      The socket file descriptor for the port to communicate on
 *      -1 on failure
 */
int initializeUDPClientSocket(char host[], char port[], struct addrinfo **serverInfo, int broadcast){
        int status;                     // To catch errors
        int socketFd;                   // File descriptor for the socket
        
        struct addrinfo hints;          // Struct to hold server info
        struct addrinfo *servinfo;      // Place to store results from getaddrinfo
        struct addrinfo *p;             // For finding a result to bind to              
        
        memset(&hints, 0, sizeof hints);        // Make sure hints is empty
        hints.ai_family = AF_UNSPEC;            // IPv4 or IPv6
        hints.ai_socktype = SOCK_DGRAM;         // Use UDP datagram sockets
        
        // Get the info in servinfo
        if((status = getaddrinfo(host, port, &hints, &servinfo)) != 0){
                fprintf(stderr, "getadrinfo errir: %s\n", gai_strerror(status));
                exit(1);
        }       
        
        // loop through our results to find a valid socket to bind to
        for(p = servinfo; p != NULL; p = p->ai_next){
                // Try to get the socket descriptor of the first result
                if((socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
                        perror("Server: Socket");
                        continue;
                }       
                
                break;
        }       
        
  // If we ran out of results and did not connect, that would be bad
        if(p == NULL){
                fprintf(stderr, "Client: Failed to create socket\n");
                exit(1);
        }       
        
        *serverInfo = p;

	if(setsockopt(socketFd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1){
		perror("setsockopt (SO_BROADCAST)");
		exit(1);
	}
        
        return socketFd;
}       

/*
 * Wrapper for closing sockets for linux and windows 
 */
void socketClose(int s){

	#ifdef __linux__
		close(s);

	#else
		closesocket(s);

	#endif
	
}
