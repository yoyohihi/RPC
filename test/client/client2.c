// Test short input/output types

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"
#include "../client.h"

int main() {
	/* prepare the arguments for f5 */
	short input[1] = {2};
	short output[2] = {1, 1};
	int count = 2;

	int argTypes[count + 1];
	argTypes[0] = (1 << ARG_INPUT) | (ARG_SHORT << 16) | 1;
	argTypes[1] = (1 << ARG_OUTPUT) | (ARG_SHORT << 16) | 2;
	argTypes[2] = 0;

	void **args;
	args = (void **)malloc(count * sizeof(void *));
	args[0] = (void *)input;
	args[1] = (void *)output;

	int s = rpcCall("f5", argTypes, args);
	/* test the return of f5 */
	printf(
	  "\nEXPECTED return of f5 is: 2 2\n"
	);

	if (s >= 0) {
	  printf("ACTUAL return of f5 is: ");
	  int i;
	  for (i = 0; i < 2; i++) {
	    printf(" %hd", *(((short *)args[1]) + i));
	  }
	  printf("\n");
	}
	else {
	  printf("Error: %d\n", s);
	}

	graceful_exit();
}