/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d3b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d3b4(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar4;
  int iVar5;
  
  FUN_0040e4a4(param_1,0xe,param_3);
  iVar1 = FUN_00409fc4(param_2);
  uVar3 = extraout_ECX;
  uVar4 = extraout_EDX;
  if (-1 < iVar1 + -1) {
    iVar5 = 0;
    do {
      FUN_0040d894(param_1,uVar4,uVar3);
      piVar2 = (int *)FUN_00409fcc(param_2,iVar5);
      FUN_0040d8e8(param_1,piVar2);
      FUN_0040d89c(param_1,extraout_EDX_00,extraout_ECX_00);
      iVar5 = iVar5 + 1;
      iVar1 = iVar1 + -1;
      uVar3 = extraout_ECX_01;
      uVar4 = extraout_EDX_01;
    } while (iVar1 != 0);
  }
  FUN_0040d89c(param_1,uVar4,uVar3);
  return;
}

