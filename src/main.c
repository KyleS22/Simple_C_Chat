#include <stdio.h>
#include <stdlib.h>
#include "simpleCChatConfig.h"
#include "list.h"

#ifdef __linux__

	#include <pthread.h>
	#include "linuxChatThreads.h"
#else
	#include <windows.h>
	#include "helloWindows.h"
#endif
 
int main(){

	char username[20];
	

	printf("Version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	printf("Welcome to simple chat!\n");
	
	printf("Please enter a user name: ");
	
	fgets(username, 20, stdin);

	

#ifdef __linux__

	pthread_t discoverThread, discoverReceiveThread, inputThread;

	if(pthread_create(&discoverThread, NULL, discoveryThread, (void*) &username) != 0){
		perror("Error Creating Discover Thread");
		exit(1);
	}

	if(pthread_create(&discoverReceiveThread, NULL, discoveryReceiverThread, (void*) &username) != 0){
		perror("Error Creating Discover Receive Thread");
		exit(1);
	}

	if(pthread_create(&inputThread, NULL, userInputThread, NULL) != 0){
		perror("Error creating user input thread");
		exit(1);
	}
	
	// TODO: Wait for exit 
	

//	exitChat();

	pthread_join(discoverThread, NULL);
	pthread_join(discoverReceiveThread, NULL);
	pthread_join(inputThread, NULL);

#else
	int *thr = malloc(sizeof(*thr));
	int *thr2 = malloc(sizeof(*thr2));

	*thr = 1;
	*thr2 = 2;

	HANDLE thread = CreateThread(NULL, 0, windowsThreadFunc, (void *) thr, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, windowsThreadFunc, (void *)thr2, 0, NULL);


#endif 

	return 0;
}
