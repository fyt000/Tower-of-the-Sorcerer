/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c5f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c5f4(int *param_1,undefined4 param_2)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  FUN_00415c64(param_1,param_2);
  if ((*(byte *)(param_1 + 7) & 1) == 0) {
    FUN_00402cdc(param_1,extraout_EDX,extraout_ECX);
  }
  return;
}

