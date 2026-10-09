/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fe1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040fe1c(int param_1,undefined param_2,undefined param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  int iVar3;
  undefined4 uVar4;
  
  *(undefined4 *)(param_1 + 0x24) = 0;
  iVar1 = FUN_0041040c(param_1);
  if (-1 < iVar1 + -1) {
    iVar3 = 0;
    do {
      uVar4 = param_4;
      iVar2 = FUN_00409a40(*(undefined4 **)(param_1 + 0x3c),iVar3);
      FUN_0040fe1c(iVar2,extraout_DL,extraout_CL,uVar4);
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

