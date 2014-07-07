// Test no input argument and no output argument

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"
#include "./client.h"

int main() {
	/* prepare the arguments for f7 */
	int count = 0;

	int argTypes[count + 1];
	argTypes[0] = 0;

	void **args;
	args = (void **)malloc(count * sizeof(void *));

	int s = rpcCall("f7", argTypes, args);
	/* test the return of f5 */
	printf(
	  "\nEXPECTED return of f7 is: \n"
	);

	if (s >= 0) {
		printf("ACTUAL return of f7 is: ");
		printf("\n");
	}
	else {
		printf("Error: %d\n", s);
	}

	graceful_exit();
}