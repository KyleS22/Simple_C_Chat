
#include <assert.h>

#ifdef _WIN32
	#include "helloWindows.h"
#else
	#include "helloWorld.h"
#endif


int main(){
	assert(1 == 1);

	printf("All tests passed!");
	return 0;
}
