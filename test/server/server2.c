// This server covers invalid test cases
// It should start after server 1

#include "../rpc.h"
#include "../server2_functions.h"

int main(int argc, char *argv[]) {

  /* create sockets and connect to the binder */
  rpcInit();

  // Test function overload
  int count2 = 1;
  int argTypes2[count2 + 1];
  argTypes2[0] = (1 << ARG_OUTPUT) | (ARG_CHAR << 16) | 100;
  argTypes2[1] = (1 << ARG_INPUT) | (ARG_FLOAT << 16);
  argTypes2[2] = (1 << ARG_INPUT) | (ARG_FLOAT << 16); // The type is changed from double to float
  argTypes2[3] = 0;
  rpcRegister("f2", argTypes2, *f2_Skel_2);

  // Testing same function call (f3) registered by two servers
  /*
   * f3 takes an array of long.
  */
  int count3 = 1;
  int argTypes3[count3 + 1];
  argTypes3[0] = (1 << ARG_OUTPUT) | (1 << ARG_INPUT) | (ARG_LONG << 16) | 11;
  argTypes3[1] = 0;
  rpcRegister("f3", argTypes3, *f3_Skel);

  // Testing same function call (f20) registered twice with different skeletons
  int count20 = 2;
  int argTypes20[count20 + 1];
  argTypes20[0] = (1 << ARG_INPUT) | (ARG_SHORT << 16) | 1;
  argTypes20[1] = (1 << ARG_OUTPUT) | (ARG_SHORT << 16) | 2;
  argTypes20[2] = 0;
  rpcRegister("f20", argTypes20, *f20_Skel);

  rpcRegister("f20", argTypes20, *f20_Skel_2);

  /* call rpcExecute */
  rpcExecute();

  /* return */
  return 0;
}
