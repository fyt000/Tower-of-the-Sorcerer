/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cf6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040cf6c(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  uint local_8;
  
  local_8 = param_3;
  FUN_0040bc08(*(int *)(param_4 + -4),&local_8,4);
  FUN_0040cf18(local_8,extraout_EDX,extraout_ECX,param_4);
  return;
}

