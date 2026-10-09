/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b944.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b944(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  uVar1 = FUN_0040ce90(param_1,param_2,param_3);
  if ((char)param_2 != (char)uVar1) {
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    uVar2 = FUN_0040cf94(param_1,extraout_EDX,extraout_ECX);
    FUN_0040b8e0(uVar2,extraout_EDX_00);
  }
  return;
}

