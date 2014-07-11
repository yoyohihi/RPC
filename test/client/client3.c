// Test no input argument and only one output argument

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"
#include "../client.h"

int main() {
	/* prepare the arguments for f6 */
	double output;
	int count = 1;

	int argTypes[count + 1];
	argTypes[0] = (1 << ARG_OUTPUT) | (ARG_DOUBLE << 16);
	argTypes[1] = 0;

	void **args;
	args = (void **)malloc(count * sizeof(void *));
	args[0] = (void *)&output;

	int s = rpcCall("f6", argTypes, args);
	/* test the return of f6 */
	printf(
		"\nEXPECTED return of f6 is: 3.14159265359\n"
	);

	if (s >= 0) {
		printf("ACTUAL return of f6 is: ");
		printf("%f\n", *((double*)args));
		printf("\n");
	}
	else {
		printf("Error: %d\n", s);
	}

	graceful_exit();
}