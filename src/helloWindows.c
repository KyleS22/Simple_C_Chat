#include <stdio.h>
#include <stdlib.h>
#include "simpleCChatConfig.h"
#include "helloWindows.h"
#include "debug.h"
#include <windows.h>

DWORD WINAPI windowsThreadFunc(void* data) {

	int num = *((int *)data);

	printf("Greetings from windows thread %i!\n", num);
	DEBUG_LOG("%s", "THIS IS A TEST FOR THE DEBUG\n");

	return 0;
}