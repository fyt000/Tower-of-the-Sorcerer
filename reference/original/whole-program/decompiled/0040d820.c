/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d820.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d820(int param_1,int param_2,undefined4 param_3)

{
  int local_8;
  
  local_8 = param_2;
  if ((-0x81 < param_2) && (param_2 < 0x80)) {
    FUN_0040e4a4(param_1,2,param_3);
    FUN_0040d260(param_1,&local_8,1);
    return;
  }
  if ((param_2 < -0x8000) || (0x7fff < param_2)) {
    FUN_0040e4a4(param_1,4,param_3);
    FUN_0040d260(param_1,&local_8,4);
  }
  else {
    FUN_0040e4a4(param_1,3,param_3);
    FUN_0040d260(param_1,&local_8,2);
  }
  return;
}

