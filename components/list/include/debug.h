/*
* debug.h
* author:
*     kyle seidenthal
*     kts135
*
* date: 26-02-18
* description Definitions for debug macros:
*/

#include <stdio.h>

#define DEBUGNRM "\x1B[0m"
#define DEBUGOK "\x1B[32m"
#define DEBUGERR "\x1B[31m"
#define DEBUGBLU "\x1B[34m"

#ifdef DEBUG
	#define DEBUG_LOG(fmt, ...) fprintf(stderr, "%sDEBUG-LOG: %s:%d:%s(): " fmt "%s", DEBUGOK, __FILE__, __LINE__, __func__, __VA_ARGS__, DEBUGNRM)
	#define DEBUG_ERR(fmt, ...) fprintf(stderr, "%sDEBUG-ERROR: %s:%d:%s(): " fmt "%s", DEBUGERR, __FILE__, __LINE__, __func__, __VA_ARGS__, DEBUGNRM)
	
	#define DEBUG_INT_ARRAY(array, length) \
		for(int i = 0; i < length; i++)\
			fprintf(stderr, "%sDEBUG-LOG: %s:%d:%s(): item %d: %d %s\n", DEBUGBLU, __FILE__, __LINE__, __func__, i,  array[i], DEBUGNRM);
#else
	#define DEBUG_LOG(fmt, ...)
	#define DEBUG_ERR(fmt, ...)
	#define DEBUG_INT_ARRAY(array, length)
#endif

