/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c26c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c26c(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 local_14 [4];
  
  uVar1 = FUN_0040ce90(param_1,param_2,param_3);
  if ((char)uVar1 == '\x05') {
    FUN_0040bc08(param_1,local_14,10);
  }
  else {
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    FUN_0040c360(param_1,extraout_EDX,extraout_ECX);
  }
  return;
}

