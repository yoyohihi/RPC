// Test calling functions that do not exist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"
#include "./client.h"

int main() {
	/* prepare the arguments for f99 */
	int count = 0;

	int argTypes[count + 1];
	argTypes[0] = 0;

	void **args;
	args = (void **)malloc(count * sizeof(void *));

	int s = rpcCall("f99", argTypes, args);

	/* test the return of f4 */
	printf("\ncalling f99 which does not exist or is not registered");
	printf("\nEXPECTED return of f99: some integer other than 0");
	printf("\nACTUAL return of f99: %d\n", s);

	graceful_exit();
}