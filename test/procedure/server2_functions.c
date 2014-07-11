#include "../server2_functions.h"
#include <stdio.h>
#include <string.h>

// Function implementations
char* f2_2(float a, float b) {

  char* ret = new char[5];
  ret[0] = '3';
  ret[1] = '1';
  ret[2] = '2';
  ret[3] = '3';

  if (a == 3.14159 && b == 1234.1001) {
    ret[4] = '5';
    return ret;
  }

  ret[4] = '0';

  return ret; 
}

void f3(long* input) {
  return;
}

void f20(short* input, short* output) {
  output[0] = input[0];
  output[1] = input[0];
  return;
}

// Skeletons
int f2_Skel_2(int *argTypes, void **args) {
  *args = f2_2( *((float *)(*(args + 1))), *((double *)(*(args + 2))) );

  return 0;  
}

int f3_Skel(int *argTypes, void **args) {

  f3((long *)(*args));
  return 0;
}

int f20_Skel(int *argTypes, void **args) {
  f20((short *) (*args), (short *) (*(args + 1)));
  return 0;
}

int f20_Skel_2(int *argTypes, void **args) {
  short* input = (short *) (*args);
  input[0] += 1;
  f5((short *) (*args), (short *) (*(args + 1)));
  return 0;
}