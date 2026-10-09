/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cef0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040cef0(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  bool bVar1;
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int *piVar2;
  
  piVar2 = (int *)(param_4 + -4);
  while( true ) {
    bVar1 = FUN_0040ba68(*piVar2,param_2,param_3);
    if (bVar1) break;
    FUN_0040cf94(*piVar2,extraout_EDX_00,extraout_ECX_00);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0040c3d4(*piVar2,extraout_EDX_00,extraout_ECX_00);
  return;
}

