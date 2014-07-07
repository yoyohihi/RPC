#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"

void graceful_exit() {
	/* rpcTerminate */
	printf("\ndo you want to terminate? y/n: ");
	if (getchar() == 'y')
		rpcTerminate();
}