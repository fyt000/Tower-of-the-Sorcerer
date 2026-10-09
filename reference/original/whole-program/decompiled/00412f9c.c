/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412f9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412f9c(int param_1,int param_2,char param_3)

{
  undefined4 extraout_ECX;
  
  FUN_0040e73c(param_1,param_2,param_3);
  if ((param_2 == *(int *)(param_1 + 0x50)) && (param_3 == '\x01')) {
    FUN_00413570(param_1,0,extraout_ECX);
  }
  return;
}

