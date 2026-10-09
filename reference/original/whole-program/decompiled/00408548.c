/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408548.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408548(int *param_1,char **param_2,undefined4 *param_3)

{
  byte abStack_10c [256];
  
  if (**param_2 == '\x05') {
    FUN_00403988(abStack_10c,param_3,0xff);
    FUN_0040842c(param_1,(int *)param_2,abStack_10c);
  }
  else {
    FUN_004084d0(param_1,(int)param_2,param_3);
  }
  return;
}

