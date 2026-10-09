/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004103dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004103dc(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != *(byte *)(param_1 + 0x2d)) {
    iVar1 = *(int *)(param_1 + 0x44);
    if (iVar1 != 0) {
      iVar2 = FUN_004106a4(iVar1,param_1);
      FUN_0041016c(iVar1,iVar2,param_2);
    }
    *(byte *)(param_1 + 0x2d) = param_2;
  }
  return;
}

