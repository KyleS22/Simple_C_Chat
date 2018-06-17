#include <stdio.h>
#include <stdlib.h>
#include "simpleCChatConfig.h"
#include <pthread.h>
#include "helloWorld.h"

void *thread(void *ptr){

	int num = *((int *) ptr);

	printf("Greetings from thread %i!\n", num);
}


//int main(){
//	printf("Version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
//
//	printf("Hello World!\n");
//	
//	pthread_t thread1, thread2;
//	int *thr = malloc(sizeof(*thr));
//	int *thr2 = malloc(sizeof(*thr2));
//
//	*thr = 1;
//	*thr2 = 2;
//	
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
//
//	return 0;
//}
