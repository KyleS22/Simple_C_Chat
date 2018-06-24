#include <stdio.h>
#include <stdlib.h>
#include "simpleCChatConfig.h"
#include "list.h"

#ifdef _WIN32
	#include <windows.h>
	#include "helloWindows.h"
#else
	#include <pthread.h>
//	#include "helloWorld.h"
#endif 
int main(){
	printf("Version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	printf("Hello World!\n");
	
#ifdef _WIN32
	int *thr = malloc(sizeof(*thr));
	int *thr2 = malloc(sizeof(*thr2));

	*thr = 1;
	*thr2 = 2;

	HANDLE thread = CreateThread(NULL, 0, windowsThreadFunc, (void *) thr, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, windowsThreadFunc, (void *)thr2, 0, NULL);

#else
//	pthread_t thread1, thread2;
//	int *thr = malloc(sizeof(*thr));
//	int *thr2 = malloc(sizeof(*thr2));
//
//	*thr = 1;
//	*thr2 = 2;
	
//	if(pthread_create(&thread1, NULL, thread, (void *) thr) != 0){
//		perror("Error Creating Thread");
//		exit(1);
//	}
//
//	if(pthread_create(&thread2, NULL, thread, (void *) thr2) != 0){
//		perror("Error Creating Thread");
//		exit(1);
//	}
//
//	pthread_join(thread1, NULL);
//	pthread_join(thread2, NULL);
#endif 

	return 0;
}
